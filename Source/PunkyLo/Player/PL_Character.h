// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PL_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPointLightComponent;
class UTextRenderComponent;
class UMaterialInstanceDynamic;

/**
 * PL_Character
 * Physical player avatar foundation.
 * Handles move, look, jump, and futuristic materialization spawn effect.
 * Phase D Step 2: carries a replicated-safe world-space nameplate driven by APlayerState::PlayerName.
 */
UCLASS()
class PUNKYLO_API APL_Character : public ACharacter
{
	GENERATED_BODY()

public:
	APL_Character();

	/** Third-person camera rig */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Scan light that sweeps down during materialization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	TObjectPtr<UPointLightComponent> SpawnScanLight;

	/** World-space nameplate floating above the character. Visual-only; driven by replicated PlayerState name. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Identity")
	TObjectPtr<UTextRenderComponent> Nameplate;

	/** Beyond this distance from the local viewer, the nameplate is hidden (UU). */
	UPROPERTY(EditDefaultsOnly, Category = "Identity")
	float NameplateMaxVisibleDistance = 3000.f;

	/** If true the local (owning) player does not see their own nameplate. */
	UPROPERTY(EditDefaultsOnly, Category = "Identity")
	bool bHideLocalPlayerNameplate = true;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// PlayerState wiring so the nameplate refreshes when replication delivers it.
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);

	// Identity / nameplate
	void BindToPlayerStateName();
	void RefreshNameplateText();
	void UpdateNameplateVisibility();

	FDelegateHandle NameChangeHandle;
	FString LastAppliedNameplateText;

	// Materialization effect state
	void StartMaterializationEffect();
	void FinishMaterializationEffect();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MatDynamic;

	float  SpawnElapsed      = 0.0f;
	float  SpawnDuration     = 1.4f;   // seconds to fully materialize
	bool   bMaterializing    = false;
	float  ScanLightStartZ   = 0.0f;   // top of scan beam in world space
	float  ScanLightEndZ     = 0.0f;   // bottom (feet)

	FTimerHandle SpawnStartTimer;
	FTimerHandle SpawnFinishTimer;
};
