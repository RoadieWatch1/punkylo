// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PL_PlayerState.generated.h"

/**
 * Broadcast on any client when this player's display name replicates/changes.
 * Pawns consume this to refresh their nameplate.
 */
DECLARE_MULTICAST_DELEGATE(FOnPLDisplayNameChanged);

/**
 * PL_PlayerState
 * Multiplayer identity foundation. Replicated per connected player.
 * Phase D Step 2: display name sourced from APlayerState::PlayerName (already replicated by engine).
 */
UCLASS()
class PUNKYLO_API APL_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APL_PlayerState();

	/** Overridden so local pawns can react to remote name replication. */
	virtual void OnRep_PlayerName() override;

	/** Fires on any client when this player's display name replicates or is set. */
	FOnPLDisplayNameChanged OnDisplayNameChanged;
};
