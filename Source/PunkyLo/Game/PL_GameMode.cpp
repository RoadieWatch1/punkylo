// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/PL_GameMode.h"
#include "Player/PL_PlayerController.h"
#include "Player/PL_Character.h"
#include "Player/PL_PlayerState.h"
#include "Game/PL_GameState.h"
#include "GameFramework/PlayerState.h"

APL_GameMode::APL_GameMode()
{
	PlayerControllerClass = APL_PlayerController::StaticClass();
	DefaultPawnClass      = APL_Character::StaticClass();
	PlayerStateClass      = APL_PlayerState::StaticClass();
	GameStateClass        = APL_GameState::StaticClass();
}

void APL_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Guarantee a non-empty, unique display name on the server. SetPlayerName replicates
	// PlayerState::PlayerName to all clients, which is what the nameplate reads.
	APlayerState* PS = NewPlayer ? NewPlayer->PlayerState : nullptr;
	if (!PS)
	{
		return;
	}

	const FString Existing = PS->GetPlayerName();
	const bool bNeedsAssignment =
		Existing.IsEmpty() ||
		Existing.Equals(TEXT("Player"), ESearchCase::IgnoreCase);

	if (bNeedsAssignment)
	{
		PS->SetPlayerName(FString::Printf(TEXT("Runner-%02d"), NextPlayerLabelIndex));
	}

	++NextPlayerLabelIndex;
}
