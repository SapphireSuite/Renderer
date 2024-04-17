// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD
#define SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD

#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 32
#define NUM_THREAD_Y 32
#define NUM_THREAD_Z 1


//---------- Outputs ----------

struct ClusterAABB
{
	float3 min;
	
	float padding1;
	
	float3 max;
	
	float padding2;
};

RWStructuredBuffer<ClusterAABB> clusterAABBs : register(u2);


//-------------------- Compute Shader --------------------

float3 ComputeScreenSpaceToViewSpace(float2 _ssPos);
float3 LineIntersectionWithZPlane(/*float3 _start, */float3 _end, float _zPlane);

[numthreads(NUM_THREAD_X, NUM_THREAD_Y, NUM_THREAD_Z)]
void main(uint3 _dispatchThreadID : SV_DispatchThreadID)
{
	if (_dispatchThreadID.x >= lightClusterInfo.gridSize.x ||
		_dispatchThreadID.y >= lightClusterInfo.gridSize.y ||
		_dispatchThreadID.z >= lightClusterInfo.gridSize.z)
		return;
	
	const float2 tilePixelSize = SA::ComputeTilePixelSize();
	
	// Compute Screen-Space min, max.
	const float2 ssMin = float2(_dispatchThreadID.x, _dispatchThreadID.y) * tilePixelSize;
	const float2 ssMax = float2(_dispatchThreadID.x + 1, _dispatchThreadID.y + 1) * tilePixelSize;
	
	// Compute View-Space min, max.
	const float3 wsMin = ComputeScreenSpaceToViewSpace(ssMin);
	const float3 wsMax = ComputeScreenSpaceToViewSpace(ssMax);

	// Compute View-Space cluster near, far.
	const float clusterNear = camera.zNear * pow(camera.zFar / camera.zNear, _dispatchThreadID.z / float(lightClusterInfo.gridSize.z));
	const float clusterFar = camera.zNear * pow(camera.zFar / camera.zNear, (_dispatchThreadID.z + 1) / float(lightClusterInfo.gridSize.z));
	
	// Compute final AABB.
	const float3 clusterMinAABB = LineIntersectionWithZPlane(wsMin, clusterNear);
	const float3 clusterMaxAABB = LineIntersectionWithZPlane(wsMax, clusterFar);
	
	// Write to buffer.
	const uint clusterIndex = _dispatchThreadID.x + _dispatchThreadID.y * min(NUM_THREAD_X, lightClusterInfo.gridSize.x) + _dispatchThreadID.z * min(NUM_THREAD_X, lightClusterInfo.gridSize.x) * min(NUM_THREAD_Y, lightClusterInfo.gridSize.y);
	clusterAABBs[clusterIndex].min = clusterMinAABB;
	clusterAABBs[clusterIndex].max = clusterMaxAABB;
}

float3 ComputeScreenSpaceToViewSpace(float2 _ssPos)
{
	// Convert to NDC
	const float2 texCoord = _ssPos / camera.screen;
	
	// Convert to clip space
	const float4 clipPos = float4(texCoord * 2.0 - 1.0, 0.0, 1.0);
	
	// Convert to view-space
	const float4 viewPos = mul(clipPos, camera.inverseProjection);
	
	// Fix perspective
	return viewPos.xyz / viewPos.w;
}

// Simplification as _start is always float3(0, 0, 0) (camera origin).
float3 LineIntersectionWithZPlane(/*float3 _start, */float3 _end, float _zPlane)
{
	// Fixed Z-based normal.
	const float3 normal = float3(0, 0, 1);
	
	// Simplification: not needed.
	//const float3 dir = _end - _start;
	
	/**
	*	Intersection formula between line and plane.
	*	t = (zPlane - dot(normal, start)) / dot(normal, dir)
	*
	*	Simplifications:
	*	> dot(normal, start) == dot(normal, float3(0, 0, 0)) == 0
	*	> dir == _end
	*/
	const float t = _zPlane / dot(normal, _end);
	
	/**
	*	Compute actual intersection point formula:
	*	intersection = start + dir * t
	*
	*	Simplifications:
	*	> start == float3(0, 0, 0)
	*	> dir == _end
	*/
	const float3 intersection = _end * t;
	
	return intersection;
}

#endif // SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD