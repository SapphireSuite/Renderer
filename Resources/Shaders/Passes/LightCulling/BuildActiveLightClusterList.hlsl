// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD
#define SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD

#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 1024
#define NUM_THREAD_Y 1
#define NUM_THREAD_Z 1

StructuredBuffer<uint> activeClusterStates : register(t1);


//---------- Outputs ----------

struct DispatchIndirectCommand
{
	uint numThreadGroupsX;
	uint numThreadGroupsY;
	uint numThreadGroupsZ;
};

RWStructuredBuffer<DispatchIndirectCommand> indirectArgs : register(u2);
RWStructuredBuffer<uint> activeClusterList : register(u3);


//-------------------- Compute Shader --------------------

[numthreads(NUM_THREAD_X, NUM_THREAD_Y, NUM_THREAD_Z)]
void main(uint3 _groupThreadID : SV_GroupThreadID)
{
	if (_groupThreadID.x == 0)
	{
		indirectArgs[0].numThreadGroupsX = 0;
	}
	
	GroupMemoryBarrierWithGroupSync();
	
	const uint totalClusterNum = lightClusterInfo.gridSize.x * lightClusterInfo.gridSize.y * lightClusterInfo.gridSize.z;

	for (uint i = _groupThreadID.x; i < totalClusterNum; i += NUM_THREAD_X)
	{
		if(activeClusterStates[i])
		{
			uint activeClusterIndex;
			InterlockedAdd(indirectArgs[0].numThreadGroupsX, 1, activeClusterIndex);
			activeClusterList[activeClusterIndex] = i;
		}
	}
}

#endif // SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD
