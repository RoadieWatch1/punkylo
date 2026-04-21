// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/PL_Character.h"
#include "Player/PL_PlayerController.h"
#include "Player/PL_PlayerState.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/PointLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

APL_Character::APL_Character()
{
	// Assign mannequin mesh so characters are visible during multiplayer replication testing.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
		TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// Standard offset: drop mesh down into capsule and rotate to face forward.
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.0f, 0.0f, -90.0f),
			FRotator(0.0f, -90.0f, 0.0f));
	}

	// Wire up the animation blueprint — without this the mesh stays in T-pose.
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(
		TEXT("/Game/Characters/Mannequins/Anims/Unarmed/ABP_Unarmed"));
	if (AnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBP.Class);
	}

	// Don't rotate the mesh with the controller; let movement handle orientation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate              = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed              = 500.0f;
	GetCharacterMovement()->MaxAcceleration           = 1200.0f;  // Smooth ramp-up
	GetCharacterMovement()->BrakingDecelerationWalking= 1000.0f;  // Smooth stop
	GetCharacterMovement()->GroundFriction            = 5.0f;     // Less ice, less stiff
	GetCharacterMovement()->JumpZVelocity             = 500.0f;
	GetCharacterMovement()->AirControl                = 0.35f;
	GetCharacterMovement()->BrakingDecelerationFalling= 200.0f;   // Natural air drift
	GetCharacterMovement()->MaxSimulationIterations   = 15;       // Prevent fall-sim overflow warning on spawn
	GetCharacterMovement()->MaxSimulationTimeStep     = 0.05f;

	// Camera boom (spring arm) — GTA-style fixed third-person camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// Fixed distance — no zoom in/out when hitting walls.
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 400.0f;
	// Slightly behind and just above the character's shoulder line.
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 80.0f);
	CameraBoom->bUsePawnControlRotation = true;
	// Smooth camera follow like GTA.
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 12.0f;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 15.0f;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	// GTA uses ~65 degree FOV for that cinematic close feel.
	FollowCamera->SetFieldOfView(65.0f);

	// Hide mesh at construction so no "naked" frame renders before BeginPlay.
	// The materialization effect in BeginPlay will reveal it with opacity = 0.
	GetMesh()->SetVisibility(false);

	// Holographic scan light — sweeps down the body during materialization.
	SpawnScanLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("SpawnScanLight"));
	SpawnScanLight->SetupAttachment(RootComponent);
	SpawnScanLight->SetIntensity(0.0f);
	SpawnScanLight->SetLightColor(FLinearColor(0.0f, 0.8f, 1.0f));  // Cyan hologram
	SpawnScanLight->SetAttenuationRadius(120.0f);
	SpawnScanLight->SetVisibility(false);

	// Nameplate — world-space text floating above the head. Text/rotation/visibility
	// are updated per-frame in Tick. Attached to root so it tracks the capsule (stable
	// under crouch/anim retargeting and safe for any mesh rig).
	Nameplate = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Nameplate"));
	Nameplate->SetupAttachment(RootComponent);
	Nameplate->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	Nameplate->SetHorizontalAlignment(EHTA_Center);
	Nameplate->SetVerticalAlignment(EVRTA_TextCenter);
	Nameplate->SetWorldSize(18.0f);
	Nameplate->SetTextRenderColor(FColor(220, 240, 255));
	Nameplate->SetText(FText::GetEmpty());
	Nameplate->SetVisibility(false);
	Nameplate->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Nameplate->SetCastShadow(false);
	Nameplate->SetGenerateOverlapEvents(false);

	PrimaryActorTick.bCanEverTick = true;
}

void APL_Character::BeginPlay()
{
	Super::BeginPlay();
	StartMaterializationEffect();
	BindToPlayerStateName();
	RefreshNameplateText();
}

void APL_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Server authoritative path: PlayerState is assigned here.
	BindToPlayerStateName();
	RefreshNameplateText();
}

void APL_Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Remote client path: PlayerState replicated down.
	BindToPlayerStateName();
	RefreshNameplateText();
}

void APL_Character::BindToPlayerStateName()
{
	APL_PlayerState* PS = GetPlayerState<APL_PlayerState>();
	if (!PS)
	{
		return;
	}

	if (NameChangeHandle.IsValid())
	{
		// Already bound — don't double-subscribe if PossessedBy + OnRep_PlayerState both fire.
		return;
	}

	NameChangeHandle = PS->OnDisplayNameChanged.AddUObject(this, &APL_Character::RefreshNameplateText);
}

void APL_Character::RefreshNameplateText()
{
	if (!Nameplate)
	{
		return;
	}

	const APlayerState* PS = GetPlayerState();
	const FString Name = PS ? PS->GetPlayerName() : FString();

	if (Name != LastAppliedNameplateText)
	{
		Nameplate->SetText(FText::FromString(Name));
		LastAppliedNameplateText = Name;
	}
}

void APL_Character::UpdateNameplateVisibility()
{
	if (!Nameplate)
	{
		return;
	}

	// No name yet → keep hidden until replication delivers it.
	if (LastAppliedNameplateText.IsEmpty())
	{
		if (Nameplate->GetVisibleFlag())
		{
			Nameplate->SetVisibility(false);
		}
		return;
	}

	// Determine the local viewer. In listen-server PIE this correctly returns the host PC
	// for the host window and the client PC for each client window — so each client sees
	// OTHER players' nameplates and (optionally) hides their own.
	APlayerController* LocalPC = GEngine ? GEngine->GetFirstLocalPlayerController(GetWorld()) : nullptr;
	if (!LocalPC || !LocalPC->PlayerCameraManager)
	{
		if (Nameplate->GetVisibleFlag())
		{
			Nameplate->SetVisibility(false);
		}
		return;
	}

	// Hide the local player's own nameplate — keeps the screen uncluttered and avoids
	// the common "my own name floating in my face" problem in third-person.
	if (bHideLocalPlayerNameplate && LocalPC->GetPawn() == this)
	{
		if (Nameplate->GetVisibleFlag())
		{
			Nameplate->SetVisibility(false);
		}
		return;
	}

	const FVector CamLoc      = LocalPC->PlayerCameraManager->GetCameraLocation();
	const FVector NameplateLoc = Nameplate->GetComponentLocation();
	const float Dist          = FVector::Dist(CamLoc, NameplateLoc);

	if (Dist > NameplateMaxVisibleDistance)
	{
		if (Nameplate->GetVisibleFlag())
		{
			Nameplate->SetVisibility(false);
		}
		return;
	}

	if (!Nameplate->GetVisibleFlag())
	{
		Nameplate->SetVisibility(true);
	}

	// Yaw-only billboard so text stays upright and legible. TextRender's readable face
	// points along the component's +X; aligning +X toward the camera makes it readable.
	// (If ever rendered mirrored in a future engine version, add 180° to Yaw.)
	FVector Flat = CamLoc - NameplateLoc;
	Flat.Z = 0.0f;
	if (!Flat.IsNearlyZero())
	{
		const FRotator LookRot = Flat.Rotation();
		Nameplate->SetWorldRotation(FRotator(0.0f, LookRot.Yaw, 0.0f));
	}
}

void APL_Character::StartMaterializationEffect()
{
	// Create a dynamic material so we can animate Opacity at runtime.
	// Set opacity to 0 immediately — mesh is already hidden in constructor,
	// so when it becomes visible the material is already transparent (no flash).
	if (GetMesh() && GetMesh()->GetMaterial(0))
	{
		MatDynamic = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
		MatDynamic->SetScalarParameterValue(TEXT("Opacity"), 0.0f);
	}

	// Calculate scan beam travel range in local space (head to toe).
	const float CapsuleHalf = GetCapsuleComponent() ? GetCapsuleComponent()->GetScaledCapsuleHalfHeight() : 48.0f;
	ScanLightStartZ = CapsuleHalf * 2.0f;   // start above head
	ScanLightEndZ   = -CapsuleHalf;          // end at feet

	// Mesh is already hidden from the constructor — lock collision only.
	// Do NOT disable movement: disabling then re-enabling causes a free-fall
	// spike at FinishMaterializationEffect that overloads the physics sim.
	// Input is blocked via bMaterializing check in HandleMove instead.
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Brief delay then begin the scan — feels like a loading beam locking on.
	// SpawnStartTimer is a member so it can be cancelled if the actor is destroyed early.
	GetWorldTimerManager().SetTimer(SpawnStartTimer, [this]()
	{
		// Opacity is already 0 — reveal mesh with no opaque flash.
		GetMesh()->SetVisibility(true);
		SpawnScanLight->SetVisibility(true);
		bMaterializing = true;
		SpawnElapsed   = 0.0f;
	}, 0.15f, false);

	// After full duration restore physics and movement.
	GetWorldTimerManager().SetTimer(SpawnFinishTimer, this,
		&APL_Character::FinishMaterializationEffect, SpawnDuration + 0.2f, false);
}

void APL_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Nameplate update runs every frame — cheap, and covers replication arriving
	// mid-session, pawn possession swaps, and local viewer movement.
	UpdateNameplateVisibility();

	if (!bMaterializing) return;

	SpawnElapsed += DeltaSeconds;
	const float Alpha = FMath::Clamp(SpawnElapsed / SpawnDuration, 0.0f, 1.0f);

	// Ease-in curve makes the end of materialization snap into place.
	const float EasedAlpha = FMath::InterpEaseIn(0.0f, 1.0f, Alpha, 2.0f);

	// Animate material opacity — 0 = transparent/hologram, 1 = solid.
	if (MatDynamic)
	{
		MatDynamic->SetScalarParameterValue(TEXT("Opacity"), EasedAlpha);
	}

	// Scan light sweeps top → bottom, brightens then fades at the end.
	const float ScanZ    = FMath::Lerp(ScanLightStartZ, ScanLightEndZ, Alpha);
	const float Pulse    = FMath::Sin(Alpha * PI);           // bright in middle, dim at ends
	const float Flicker  = FMath::RandRange(0.85f, 1.0f);   // holographic flicker
	SpawnScanLight->SetRelativeLocation(FVector(0.0f, 0.0f, ScanZ));
	SpawnScanLight->SetIntensity(8000.0f * Pulse * Flicker);

	// Shift color from cold cyan → warm white as character solidifies.
	const FLinearColor ScanColor = FLinearColor::LerpUsingHSV(
		FLinearColor(0.0f, 0.8f, 1.0f),   // cyan hologram
		FLinearColor(0.6f, 0.9f, 1.0f),   // cool white
		EasedAlpha);
	SpawnScanLight->SetLightColor(ScanColor);

	if (Alpha >= 1.0f)
	{
		bMaterializing = false;
	}
}

void APL_Character::FinishMaterializationEffect()
{
	bMaterializing = false;

	// Ensure the start-delay timer can't fire after we're done.
	GetWorldTimerManager().ClearTimer(SpawnStartTimer);

	// Restore full opacity, physics, and movement.
	if (MatDynamic)
	{
		MatDynamic->SetScalarParameterValue(TEXT("Opacity"), 1.0f);
	}

	SpawnScanLight->SetIntensity(0.0f);
	SpawnScanLight->SetVisibility(false);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APL_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	APL_PlayerController* PC     = Cast<APL_PlayerController>(GetController());

	if (!EIC || !PC)
	{
		return;
	}

	if (PC->MoveAction)
	{
		EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &APL_Character::HandleMove);
	}

	if (PC->LookAction)
	{
		EIC->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &APL_Character::HandleLook);
	}

	if (PC->JumpAction)
	{
		EIC->BindAction(PC->JumpAction, ETriggerEvent::Started,   this, &ACharacter::Jump);
		EIC->BindAction(PC->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void APL_Character::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MoveVec = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Project movement onto the controller's yaw plane.
		const FRotator YawRot(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector  Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector  Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, MoveVec.Y); // Y = forward/back
		AddMovementInput(Right,   MoveVec.X); // X = strafe right/left
	}
}

void APL_Character::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookVec = Value.Get<FVector2D>();

	AddControllerYawInput(LookVec.X);
	AddControllerPitchInput(LookVec.Y);
}
