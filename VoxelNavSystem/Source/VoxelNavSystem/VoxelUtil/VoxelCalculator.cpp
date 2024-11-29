// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelCalculator.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void VoxelCalculator::CalcRootAABB(IN SparseVoxelOctreeNode* InRootNode, IN ChunkIndex InChunkIndex)
{
	InRootNode->SetNodeSize(CHUNK_SIZE);

	float newNodeSize = CHUNK_SIZE / 2.0f;

	InRootNode->m_AabbCenter.X = InChunkIndex.x * CHUNK_SIZE;
	InRootNode->m_AabbCenter.Y = InChunkIndex.y * CHUNK_SIZE;
	InRootNode->m_AabbCenter.Z = InChunkIndex.z * CHUNK_SIZE;

	InRootNode->m_AabbMin.X = InRootNode->m_AabbCenter.X - newNodeSize;
	InRootNode->m_AabbMin.Y = InRootNode->m_AabbCenter.Y - newNodeSize;
	InRootNode->m_AabbMin.Z = InRootNode->m_AabbCenter.Z - newNodeSize;

	InRootNode->m_AabbMax.X = InRootNode->m_AabbCenter.X + newNodeSize;
	InRootNode->m_AabbMax.Y = InRootNode->m_AabbCenter.Y + newNodeSize;
	InRootNode->m_AabbMax.Z = InRootNode->m_AabbCenter.Z + newNodeSize;
}

void VoxelCalculator::CalcAABB(IN FVector InAABBCenter, IN int InChildIndex, IN float InCurrentNodeSize, OUT FVector OutAABBMin, OUT FVector OutAABBMax, OUT FVector OutAABBCenter)
{
	float newNodeSize = InCurrentNodeSize / 2.0f;

	OutAABBCenter.X = InChildIndex % 1 ? InAABBCenter.X - newNodeSize : InAABBCenter.X + newNodeSize;
	OutAABBCenter.Y = InChildIndex % 2 ? InAABBCenter.Y + newNodeSize : InAABBCenter.Y - newNodeSize;
	OutAABBCenter.Z = InChildIndex % 4 ? InAABBCenter.Z - newNodeSize : InAABBCenter.Z - newNodeSize;

	OutAABBMin.X = OutAABBCenter.X - newNodeSize;
	OutAABBMin.Y = OutAABBCenter.Y - newNodeSize;
	OutAABBMin.Z = OutAABBCenter.Z - newNodeSize;

	OutAABBMax.X = OutAABBCenter.X + newNodeSize;
	OutAABBMax.Y = OutAABBCenter.X + newNodeSize;
	OutAABBMax.Z = OutAABBCenter.X + newNodeSize;
}

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

bool VoxelCalculator::HasCollision(IN FVector InAABBMin, IN FVector INAABBMax)
{
	return false;
}
