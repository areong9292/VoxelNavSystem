// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "../VoxelUtil/VoxelCalculator.h"

// class that has all voxels
class VoxelManager
{
public:
	// Build Chunk In Current Pos
	static void BuildChunkInCurrentPos(IN const AActor* InCurrentPlayer);

	// VoxelMap
	//TMap<VoxelKey, VoxelData> m_VoxelMap;
};