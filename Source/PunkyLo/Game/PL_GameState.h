// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "PL_GameState.generated.h"

/**
 * PL_GameState
 * Shared world data foundation. Replicated to all connected clients.
 */
UCLASS()
class PUNKYLO_API APL_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APL_GameState();
};
