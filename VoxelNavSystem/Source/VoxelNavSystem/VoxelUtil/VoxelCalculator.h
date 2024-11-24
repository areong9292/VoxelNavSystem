// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "VoxelData.h"

// class that voxel calculate
class VoxelCalculator
{
public:
	static void CalcChunkIndex(IN FVector InCurrentPos, OUT ChunkIndex& OutChunkIndex);
	static void CalcVoxelKey(IN FVector InCurrentPos, OUT VoxelKey& outVoxelKey);

};