// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/PL_PlayerState.h"

APL_PlayerState::APL_PlayerState()
{
}

void APL_PlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();
	OnDisplayNameChanged.Broadcast();
}
