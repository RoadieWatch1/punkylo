// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "PL_GameMode.generated.h"

/**
 * PL_GameMode
 * Server authority logic foundation. Sets default framework classes and assigns
 * a server-authoritative display name to each connecting player so the replicated
 * identity layer always has a legible value to show.
 */
UCLASS()
class PUNKYLO_API APL_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APL_GameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	// Monotonically increasing label index for auto-generated names. Server-only.
	int32 NextPlayerLabelIndex = 0;
};
