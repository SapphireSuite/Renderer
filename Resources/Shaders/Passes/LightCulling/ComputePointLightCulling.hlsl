// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_COMPUTE_POINT_LIGHT_CULLING_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPUTE_POINT_LIGHT_CULLING_GUARD

#include <Common/Misc/AABB.hlsl>
#include <Common/Camera.hlsl>
#include <Common/Lighting/PointLight.hlsl>

/**
*	Cluster-based implementation:
*	Compute shader is dispatched for each active cluster.
*	Each instance compute culling for all point lights for the current cluster.
*/


//---------- Inputs ----------

#define NUM_THREAD_X 1024

StructuredBuffer<SA::AABB> lightClusterAABBs : register(t2);

StructuredBuffer<uint> activeClusterList : register(t3);


//---------- Shared ----------

groupshared uint pLightNum;
groupshared uint activeClusterIndex;
groupshared SA::AABB currLightClusterAABB;


//---------- Outputs ----------

struct ClusterPointLightList
{
	/// Number of lights in the cluster.
	uint num;
	
	/// Light indices in the cluster.
	uint lightIndices[63]; // Maximum of 63 lights per cluster.
};

RWStructuredBuffer<ClusterPointLightList> culledPointLightGrid : register(u4);


//-------------------- Compute Shader --------------------

bool SphereAABBCollision(SA::PointLight _plight, SA::AABB _aabb);

[numthreads(NUM_THREAD_X, 1, 1)]
void main(uint _groupID : SV_GroupID, uint _groupThreadID : SV_GroupThreadID)
{
	//---------- Init ----------
	
	if(_groupThreadID == 0)
	{
		uint lightStride;
		SA::pointLights.GetDimensions(pLightNum, lightStride);
		
		activeClusterIndex = activeClusterList[_groupID];
		currLightClusterAABB = lightClusterAABBs[activeClusterIndex];
		
		// Clear previous value.
		culledPointLightGrid[activeClusterIndex].num = 0;
	}
	
	GroupMemoryBarrierWithGroupSync();
	
	
	//---------- Collision check ----------
	
	const uint numBatches = (pLightNum + NUM_THREAD_X - 1) / NUM_THREAD_X;
	
	for (uint batchIndex = 0; batchIndex < numBatches; ++batchIndex)
	{
		const uint lightIndex = batchIndex * NUM_THREAD_X + _groupThreadID;

		if (lightIndex >= pLightNum)
			continue;
		
		const SA::PointLight plight = SA::pointLights[lightIndex];
		
		if (SphereAABBCollision(plight, currLightClusterAABB))
		{
			uint offset;
			InterlockedAdd(culledPointLightGrid[activeClusterIndex].num, 1, offset);
			
			culledPointLightGrid[activeClusterIndex].lightIndices[offset] = lightIndex;
		}
	}
}

bool SphereAABBCollision(SA::PointLight _plight, SA::AABB _aabb)
{
	/**
	*	Convert light position to view space.
	*	Calculation are done in view space.
	*/
	const float3 vsLightCenter = mul(camera.view, float4(_plight.position, 1.0)).xyz;
	
	// Closest point in AABB.
	const float3 closestAABB = clamp(vsLightCenter, _aabb.min, _aabb.max);
	
	const float3 vLightToClosest = closestAABB - vsLightCenter;
	
	const float squaredDistance = dot(vLightToClosest, vLightToClosest);
	
	return squaredDistance <= _plight.radius * _plight.radius;
}

#endif // SAPPHIRE_RENDER_SHADER_COMPUTE_POINT_LIGHT_CULLING_GUARD
