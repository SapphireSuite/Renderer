// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD
#define SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD

#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 1024

StructuredBuffer<uint> activeClusterStates : register(t1);


//---------- Shared ----------

/// Current registered light number.
groupshared uint activeClusterNum;


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

[numthreads(NUM_THREAD_X, 1, 1)]
void main(uint _groupThreadID : SV_GroupThreadID)
{
	//---------- Init ----------
	
	if (_groupThreadID == 0)
	{
		activeClusterNum = 0;
	}
	
	GroupMemoryBarrierWithGroupSync();
	
	
	//---------- Build Active list ----------
	
	const uint totalClusterNum = lightClusterInfo.gridSize.x * lightClusterInfo.gridSize.y * lightClusterInfo.gridSize.z;

	for (uint i = _groupThreadID; i < totalClusterNum; i += NUM_THREAD_X)
	{
		if(activeClusterStates[i])
		{
			uint activeClusterIndex;
			InterlockedAdd(activeClusterNum, 1, activeClusterIndex);
			activeClusterList[activeClusterIndex] = i;
		}
	}
	
	
	//---------- Output ----------
	
	if (_groupThreadID == 0)
	{
		indirectArgs[0].numThreadGroupsX = activeClusterNum;
		indirectArgs[0].numThreadGroupsY = 1;
		indirectArgs[0].numThreadGroupsZ = 1;
	}
}

#endif // SAPPHIRE_RENDER_SHADER_BUILD_ACTIVE_LIGHT_CLUSTER_LIST_GUARD
