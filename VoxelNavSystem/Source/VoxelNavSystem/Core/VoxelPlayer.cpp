// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelPlayer.h"
#include "../VoxelManager/VoxelManager.h"

void AVoxelPlayer::BuildChunkInCurrentPos()
{
	VoxelManager::BuildChunkInCurrentPos(this);
}
