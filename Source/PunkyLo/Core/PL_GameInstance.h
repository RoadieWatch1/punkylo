// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "PL_GameInstance.generated.h"

/**
 * PL_GameInstance
 * Global state foundation. Persists across level transitions.
 * Owns long-lived subsystems for networking and world management.
 */
UCLASS()
class PUNKYLO_API UPL_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPL_GameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;
};
