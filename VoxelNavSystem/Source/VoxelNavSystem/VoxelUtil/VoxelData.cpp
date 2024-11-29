// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelData.h"

SparseVoxelOctreeNode::SparseVoxelOctreeNode()
{
	// Octree has 8 childs
	m_ChildNode.Reserve(8);
}

SparseVoxelOctreeNode::~SparseVoxelOctreeNode()
{
}
