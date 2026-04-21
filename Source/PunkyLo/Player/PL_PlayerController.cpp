// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/PL_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "EnhancedActionKeyMapping.h"

APL_PlayerController::APL_PlayerController()
{
}

void APL_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Load Input Actions from content. If assets don't exist yet (editor not run),
	// NewObject fallbacks are created so input still compiles and binds correctly.
	MoveAction = LoadObject<UInputAction>(nullptr,
		TEXT("/Game/Core/Blueprints/Input/Actions/IA_Move.IA_Move"));
	LookAction = LoadObject<UInputAction>(nullptr,
		TEXT("/Game/Core/Blueprints/Input/Actions/IA_Look.IA_Look"));
	JumpAction = LoadObject<UInputAction>(nullptr,
		TEXT("/Game/Core/Blueprints/Input/Actions/IA_Jump.IA_Jump"));

	// Fallback: create transient action objects if assets are absent.
	if (!MoveAction)
	{
		MoveAction = NewObject<UInputAction>(this, TEXT("IA_Move_Transient"));
		MoveAction->ValueType = EInputActionValueType::Axis2D;
	}
	if (!LookAction)
	{
		LookAction = NewObject<UInputAction>(this, TEXT("IA_Look_Transient"));
		LookAction->ValueType = EInputActionValueType::Axis2D;
	}
	if (!JumpAction)
	{
		JumpAction = NewObject<UInputAction>(this, TEXT("IA_Jump_Transient"));
		JumpAction->ValueType = EInputActionValueType::Boolean;
	}

	BuildAndRegisterIMC();
}

void APL_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	// IMC is already built in BeginPlay. Only register it if it somehow isn't yet
	// (e.g. late join). Building it twice per spawn was doubling all NewObject calls.
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem && DefaultMappingContext && !Subsystem->HasMappingContext(DefaultMappingContext))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APL_PlayerController::BuildAndRegisterIMC()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem)
	{
		return;
	}

	// Build the IMC programmatically so modifiers are always correct,
	// regardless of whether the content asset has been populated.
	DefaultMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Default_Runtime"));

	// -------------------------------------------------------
	// Movement: IA_Move (Axis2D — X = right, Y = forward)
	// -------------------------------------------------------

	// D  →  +X  (no modifier; key press gives (1,0,0))
	DefaultMappingContext->MapKey(MoveAction, EKeys::D);

	// A  →  -X  (Negate)
	{
		FEnhancedActionKeyMapping& M = DefaultMappingContext->MapKey(MoveAction, EKeys::A);
		UInputModifierNegate* Neg = NewObject<UInputModifierNegate>(DefaultMappingContext);
		M.Modifiers.Add(Neg);
	}

	// W  →  +Y  (SwizzleAxis YXZ: (1,0,0) → (0,1,0))
	{
		FEnhancedActionKeyMapping& M = DefaultMappingContext->MapKey(MoveAction, EKeys::W);
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(DefaultMappingContext);
		Swizzle->Order = EInputAxisSwizzle::YXZ;
		M.Modifiers.Add(Swizzle);
	}

	// S  →  -Y  (SwizzleAxis YXZ then Negate)
	{
		FEnhancedActionKeyMapping& M = DefaultMappingContext->MapKey(MoveAction, EKeys::S);
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(DefaultMappingContext);
		Swizzle->Order = EInputAxisSwizzle::YXZ;
		UInputModifierNegate* Neg = NewObject<UInputModifierNegate>(DefaultMappingContext);
		M.Modifiers.Add(Swizzle);
		M.Modifiers.Add(Neg);
	}

	// Gamepad left stick 2D (X = right, Y = forward — no modifier needed)
	DefaultMappingContext->MapKey(MoveAction, EKeys::Gamepad_Left2D);

	// -------------------------------------------------------
	// Look: IA_Look (Axis2D — X = yaw, Y = pitch)
	// -------------------------------------------------------

	// Mouse2D: scale raw pixel delta to reasonable angular velocity
	{
		FEnhancedActionKeyMapping& M = DefaultMappingContext->MapKey(LookAction, EKeys::Mouse2D);
		UInputModifierScalar* Scale = NewObject<UInputModifierScalar>(DefaultMappingContext);
		Scale->Scalar = FVector(0.4f, 0.4f, 1.0f);
		M.Modifiers.Add(Scale);
	}

	// Gamepad right stick 2D (no modifier; already -1..+1)
	DefaultMappingContext->MapKey(LookAction, EKeys::Gamepad_Right2D);

	// -------------------------------------------------------
	// Jump: IA_Jump (Bool)
	// -------------------------------------------------------
	DefaultMappingContext->MapKey(JumpAction, EKeys::SpaceBar);
	DefaultMappingContext->MapKey(JumpAction, EKeys::Gamepad_FaceButton_Bottom);

	// Register with priority 0 (default layer)
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}
