// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "PL_NetworkSubsystem.generated.h"

/**
 * PL_NetworkSubsystem
 * Service-layer subsystem for session and connection management.
 * Lives on the GameInstance; persists across level transitions.
 */
UCLASS()
class PUNKYLO_API UPL_NetworkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
