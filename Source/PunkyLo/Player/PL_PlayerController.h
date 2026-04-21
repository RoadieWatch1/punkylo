// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PL_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * PL_PlayerController
 * Input handling layer. Builds and registers the Enhanced Input mapping context.
 * Exposes action pointers so the possessed character can bind handlers.
 */
UCLASS()
class PUNKYLO_API APL_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APL_PlayerController();

	/** Loaded at BeginPlay from Content/Core/Blueprints/Input/Actions/ */
	UPROPERTY(BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> JumpAction;

protected:
	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* P) override;

private:
	/** Keeps the programmatic IMC alive (not GC'd). */
	UPROPERTY()
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	void BuildAndRegisterIMC();
};
