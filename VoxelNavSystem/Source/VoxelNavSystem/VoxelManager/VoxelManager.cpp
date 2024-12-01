// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelManager.h"

void VoxelManager::BuildChunkInCurrentPos(IN FVector InCurrentPos)
{
	// Calc Current ChunkIndex
	ChunkIndex CurrentChunkIndex;
	VoxelCalculator::CalcChunkIndex(InCurrentPos, CurrentChunkIndex);

	// Do Build
	// SVO(Sparse Voxel Octree) Algorithm

	// Init Root
	SparseVoxelOctreeNode rootNode;
	VoxelCalculator::CalcRootAABB(&rootNode, CurrentChunkIndex);

	TArray<SparseVoxelOctreeNode> parentNode;
	parentNode.Add(rootNode);

	while (parentNode.Num() > 0)
	{
		for (int i = 0; i < parentNode.Num(); i++)
		{
			SparseVoxelOctreeNode nowParent = parentNode[i];

		}
	}
}
