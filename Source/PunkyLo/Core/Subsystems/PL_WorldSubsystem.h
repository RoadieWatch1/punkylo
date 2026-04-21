// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "PL_WorldSubsystem.generated.h"

/**
 * PL_WorldSubsystem
 * Service-layer subsystem for per-world state management.
 * Instantiated once per UWorld; torn down on level unload.
 */
UCLASS()
class PUNKYLO_API UPL_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
