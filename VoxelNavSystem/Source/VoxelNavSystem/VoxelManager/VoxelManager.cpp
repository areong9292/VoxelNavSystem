// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelManager.h"

void VoxelManager::BuildChunkInCurrentPos(IN const AActor* InCurrentPlayer)
{
	if (!IsValid(InCurrentPlayer))
	{
		return;
	}

	// Calc Current ChunkIndex
	ChunkIndex CurrentChunkIndex;
	VoxelCalculator::CalcChunkIndex(InCurrentPlayer->GetActorLocation(), CurrentChunkIndex);

	UE_LOG(LogTemp, Warning, TEXT("Current ChunkIndex - %d, %d, %d"), CurrentChunkIndex.x, CurrentChunkIndex.y, CurrentChunkIndex.z);

	// Do Build
	// SVO(Sparse Voxel Octree) Algorithm

	// Init Root
	SparseVoxelOctreeNode rootNode;
	VoxelCalculator::CalcRootAABB(&rootNode, CurrentChunkIndex);

	TArray<SparseVoxelOctreeNode> parentNode;
	TArray<SparseVoxelOctreeNode> newParentNode;
	parentNode.Add(rootNode);

	while (parentNode.Num() > 0)
	{
		for (int i = 0; i < parentNode.Num(); i++)
		{
			SparseVoxelOctreeNode nowParent = parentNode[i];

			// if CurrentParent is Leaf Node or End Node
			// No More loop
			if (nowParent.m_IsLeafNode || nowParent.m_IsEndNode)
			{
				continue;
			}

			// Init ChildNode
			for (int j = 0; j < 8; j++)
			{
				SparseVoxelOctreeNode childNode;
				nowParent.m_ChildNode.Add(childNode);
			}

			for (int j = 0; j < nowParent.m_ChildNode.Num(); j++)
			{
				// Set ChildNode
				SparseVoxelOctreeNode childNode;
				VoxelCalculator::CalcAABB(nowParent.m_AabbCenter, j, nowParent.m_NodeSize, &childNode);

				nowParent.m_ChildNode[j] = childNode;

				// check HasCollision In ChildNode
				FHitResult HitResult;
				bool bHasCollision = VoxelCalculator::HasCollision(InCurrentPlayer, childNode, HitResult);

				// if HasCollision
				if (bHasCollision)
				{
					// if ChildNode == VOXEL
					// is LeafNode
					if (childNode.m_NodeSize <= VOXEL_SIZE)
					{
						childNode.m_IsLeafNode = true;

						// Set SubVoxel
						{

						}
					}

					// if ChildNdoe != VOXEL
					// Next Step SVO
					else
					{
						newParentNode.Add(childNode);
					}
				}

				// else
				// EndNode
				else
				{
					childNode.m_IsEndNode = true;
				}
			}
		}

		// Set NewParent to Parent
		parentNode.Empty();
		parentNode.Reserve(newParentNode.Num());

		for (int i = 0; i < newParentNode.Num(); i++)
		{
			parentNode.Add(newParentNode[i]);
		}

		newParentNode.Empty();
	}
}
