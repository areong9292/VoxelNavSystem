// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "VoxelData.h"

// class that voxel calculate
class VoxelCalculator
{
public:
	static void CalcRootAABB(IN SparseVoxelOctreeNode* InRootNode, IN ChunkIndex InChunkIndex);
	static void CalcAABB(IN FVector InAABBCenter, IN short InChildIndex, IN float InCurrentNodeSize, OUT SparseVoxelOctreeNode* OutChildNode);
	static void CalcChunkIndex(IN FVector InCurrentPos, OUT ChunkIndex& OutChunkIndex);
	static void CalcVoxelKey(IN FVector InCurrentPos, OUT VoxelKey& outVoxelKey);
	static bool HasCollision(IN const AActor* InCurrentPlayer, IN SparseVoxelOctreeNode InNode, OUT FHitResult& OutHitResult);
};