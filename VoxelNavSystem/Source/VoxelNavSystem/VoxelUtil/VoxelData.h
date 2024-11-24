// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#define MAX_CHUNK_SIZE 128
#define VOXEL_SIZE 100

// 1 Chunk = VOXEL_COUNT_IN_CHUNK * VOXEL_COUNT_IN_CHUNK * VOXEL_COUNT_IN_CHUNK Voxel
#define VOXEL_COUNT_IN_CHUNK 100
#define CHUNK_SIZE (VOXEL_COUNT_IN_CHUNK * VOXEL_SIZE)

struct ChunkIndex
{
	short x;
	short y;
	short z;
};

struct VoxelKey
{
	short x;
	short y;
	short z;
};

// SubVoxel divides a voxel into eight parts(SVO)
struct SubVoxel
{
	short bHasCollsion0;
	short subVoxelType0;

	short bHasCollsion1;
	short subVoxelType1;

	short bHasCollsion2;
	short subVoxelType2;

	short bHasCollsion3;
	short subVoxelType3;

	short bHasCollsion4;
	short subVoxelType4;

	short bHasCollsion5;
	short subVoxelType5;

	short bHasCollsion6;
	short subVoxelType6;

	short bHasCollsion7;
	short subVoxelType7;
};

class VoxelData
{
	VoxelKey m_VoxelKey;
	SubVoxel m_SubVoxel;
};