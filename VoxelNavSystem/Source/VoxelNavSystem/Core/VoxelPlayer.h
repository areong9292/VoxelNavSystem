// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelPlayer.generated.h"

UCLASS()
class AVoxelPlayer : public ACharacter
{
GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void BuildChunkInCurrentPos();
};