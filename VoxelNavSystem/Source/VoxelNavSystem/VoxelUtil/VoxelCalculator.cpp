// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelCalculator.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void VoxelCalculator::CalcRootAABB(IN SparseVoxelOctreeNode* InRootNode, IN ChunkIndex InChunkIndex)
{
	InRootNode->SetNodeSize(CHUNK_SIZE);

	float newNodeSize = CHUNK_SIZE / 2.0f;
	float newNodeSizeHalf = newNodeSize / 2.0f;

	InRootNode->m_AabbCenter.X = InChunkIndex.x * CHUNK_SIZE;
	InRootNode->m_AabbCenter.Y = InChunkIndex.y * CHUNK_SIZE;
	InRootNode->m_AabbCenter.Z = InChunkIndex.z * CHUNK_SIZE;

	InRootNode->m_AabbMin.X = InRootNode->m_AabbCenter.X - newNodeSizeHalf;
	InRootNode->m_AabbMin.Y = InRootNode->m_AabbCenter.Y - newNodeSizeHalf;
	InRootNode->m_AabbMin.Z = InRootNode->m_AabbCenter.Z - newNodeSizeHalf;

	InRootNode->m_AabbMax.X = InRootNode->m_AabbCenter.X + newNodeSizeHalf;
	InRootNode->m_AabbMax.Y = InRootNode->m_AabbCenter.Y + newNodeSizeHalf;
	InRootNode->m_AabbMax.Z = InRootNode->m_AabbCenter.Z + newNodeSizeHalf;
}

void VoxelCalculator::CalcAABB(IN FVector InAABBCenter, IN short InChildIndex, IN float InCurrentNodeSize, OUT SparseVoxelOctreeNode* OutChildNode)
{
	float newNodeSize = InCurrentNodeSize / 2.0f;
	float newNodeSizeHalf = newNodeSize / 2.0f;

	OutChildNode->SetNodeSize(newNodeSize);

	OutChildNode->m_AabbCenter.X = InChildIndex & 1 ? InAABBCenter.X + newNodeSizeHalf : InAABBCenter.X - newNodeSizeHalf;
	OutChildNode->m_AabbCenter.Y = InChildIndex & 2 ? InAABBCenter.Y - newNodeSizeHalf : InAABBCenter.Y + newNodeSizeHalf;
	OutChildNode->m_AabbCenter.Z = InChildIndex & 4 ? InAABBCenter.Z + newNodeSizeHalf : InAABBCenter.Z - newNodeSizeHalf;

	//UE_LOG(LogTemp, Warning, TEXT("InChildIndex - %d"), InChildIndex);

	//if (InChildIndex & 1)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("1 true"));
	//}

	//if (InChildIndex & 2)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("2 true"));
	//}

	//if (InChildIndex & 4)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("4 true"));
	//}

	//UE_LOG(LogTemp, Warning, TEXT("OutChildNode->m_AabbCenter: X - %f, Y - %f, Z - %f"), OutChildNode->m_AabbCenter.X, OutChildNode->m_AabbCenter.Y, OutChildNode->m_AabbCenter.Z);

	OutChildNode->m_AabbMin.X = OutChildNode->m_AabbCenter.X - newNodeSizeHalf;
	OutChildNode->m_AabbMin.Y = OutChildNode->m_AabbCenter.Y - newNodeSizeHalf;
	OutChildNode->m_AabbMin.Z = OutChildNode->m_AabbCenter.Z - newNodeSizeHalf;

	OutChildNode->m_AabbMax.X = OutChildNode->m_AabbCenter.X + newNodeSizeHalf;
	OutChildNode->m_AabbMax.Y = OutChildNode->m_AabbCenter.Y + newNodeSizeHalf;
	OutChildNode->m_AabbMax.Z = OutChildNode->m_AabbCenter.Z + newNodeSizeHalf;
}

void VoxelCalculator::CalcChunkIndex(IN FVector InCurrentPos, OUT ChunkIndex& OutChunkIndex)
{
	// Chunk index is the center point of the chunk.	
	OutChunkIndex.x = InCurrentPos.X / (CHUNK_SIZE / 2.0f);
	OutChunkIndex.y = InCurrentPos.Y / (CHUNK_SIZE / 2.0f);
	OutChunkIndex.z = InCurrentPos.Z / (CHUNK_SIZE / 2.0f);
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

bool VoxelCalculator::HasCollision(IN const AActor* InCurrentPlayer, IN SparseVoxelOctreeNode InNode, OUT FHitResult& OutHitResult)
{
	if (!IsValid(InCurrentPlayer))
	{
		return false;
	}

	UWorld* CurrentWorld = InCurrentPlayer->GetWorld();

	if (!IsValid(CurrentWorld))
	{
		return false;
	}

	FVector StartLocation = FVector(InNode.m_AabbCenter.X, InNode.m_AabbCenter.Y, InNode.m_AabbMin.Z);
	FVector EndLocation = FVector(InNode.m_AabbCenter.X, InNode.m_AabbCenter.Y, InNode.m_AabbMax.Z);

	FVector BoxExtent = FVector(InNode.m_NodeSize / 2.0f, InNode.m_NodeSize / 2.0f, InNode.m_NodeSize / 2.0f);
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxExtent);

	// Only Draw Voxel
	if (InNode.m_NodeSize <= 50.0f)
	{
		DrawDebugBox(CurrentWorld, InNode.m_AabbCenter, BoxExtent, FColor::Red, false, 10.0f);
	}

	bool bHasHit = CurrentWorld->SweepSingleByChannel(OutHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, CollisionShape);
	
	return bHasHit;
}
