// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelCalculator.h"

void VoxelCalculator::CalcChunkIndex(IN FVector InCurrentPos, OUT ChunkIndex& OutChunkIndex)
{
	OutChunkIndex.x = InCurrentPos.X / CHUNK_SIZE;
	OutChunkIndex.y = InCurrentPos.Y / CHUNK_SIZE;
	OutChunkIndex.z = InCurrentPos.Z / CHUNK_SIZE;
}

void VoxelCalculator::CalcVoxelKey(IN FVector InCurrentPos, OUT VoxelKey& outVoxelKey)
{
	ChunkIndex ChunkIndex;

	ChunkIndex.x = InCurrentPos.X / CHUNK_SIZE;
	ChunkIndex.y = InCurrentPos.Y / CHUNK_SIZE;
	ChunkIndex.z = InCurrentPos.Z / CHUNK_SIZE;

	outVoxelKey.x = InCurrentPos.X - ChunkIndex.x * CHUNK_SIZE;
	outVoxelKey.y = InCurrentPos.Y - ChunkIndex.y * CHUNK_SIZE;
	outVoxelKey.z = InCurrentPos.Z - ChunkIndex.z * CHUNK_SIZE;
}
