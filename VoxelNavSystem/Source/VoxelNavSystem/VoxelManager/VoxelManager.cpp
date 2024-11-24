// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelManager.h"
#include "../VoxelUtil/VoxelCalculator.h"

void VoxelManager::BuildChunkInCurrentPos(IN FVector InCurrentPos)
{
	ChunkIndex CurrentChunkIndex;
	VoxelCalculator::CalcChunkIndex(InCurrentPos, CurrentChunkIndex);
}
