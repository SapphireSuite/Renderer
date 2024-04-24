// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD
#define SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD

#include <Common/Misc/AABB.hlsl>
#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 32
#define NUM_THREAD_Y 32
#define NUM_THREAD_Z 1


//---------- Outputs ----------

RWStructuredBuffer<SA::AABB> lightClusterAABBs : register(u2);


//-------------------- Compute Shader --------------------

float2 ComputeScreenSpaceToViewSpace(float2 _ssPos);
float3 LineIntersectionWithZPlane(float2 _dirXY, float _zPlane);

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
	const float2 vsMin = ComputeScreenSpaceToViewSpace(ssMin);
	const float2 vsMax = ComputeScreenSpaceToViewSpace(ssMax);

	// Compute View-Space cluster near, far.
	const float clusterNear = camera.zNear * pow(camera.zFar / camera.zNear, _dispatchThreadID.z / float(lightClusterInfo.gridSize.z));
	const float clusterFar = camera.zNear * pow(camera.zFar / camera.zNear, (_dispatchThreadID.z + 1) / float(lightClusterInfo.gridSize.z));
	
	// Compute final AABB.
	const float3 minPointFar = LineIntersectionWithZPlane(vsMin, clusterFar);
	const float3 maxPointFar = LineIntersectionWithZPlane(vsMax, clusterFar);
	const float3 clusterMinAABB = float3(minPointFar.x, maxPointFar.y, clusterNear); // Swap min/max y because Y-axis is flipped.
	const float3 clusterMaxAABB = float3(maxPointFar.x, minPointFar.y, clusterFar); // Swap min/max y because Y-axis is flipped.
	
	// Write to buffer.
	const uint clusterIndex = _dispatchThreadID.x + _dispatchThreadID.y * min(NUM_THREAD_X, lightClusterInfo.gridSize.x) + _dispatchThreadID.z * min(NUM_THREAD_X, lightClusterInfo.gridSize.x) * min(NUM_THREAD_Y, lightClusterInfo.gridSize.y);
	lightClusterAABBs[clusterIndex].min = clusterMinAABB;
	lightClusterAABBs[clusterIndex].max = clusterMaxAABB;
}

float2 ComputeScreenSpaceToViewSpace(float2 _ssPos)
{
	// Convert to NDC
	const float2 texCoord = _ssPos / camera.screen;
	
	// Convert to clip space
	float4 clipPos = float4(texCoord * 2.0 - 1.0, 0.0, 1.0);
	
	// Viewport is flipped so Y-axis needs to be reversed.
	clipPos.y = -clipPos.y;
	
	// Convert to view-space
	const float4 viewPos = mul(clipPos, camera.inverseProjection);
	
	// Fix perspective
	return viewPos.xy / viewPos.w;
}

float3 LineIntersectionWithZPlane(float2 _dirXY, float _zPlane)
{
	/**
	*	Intersection formula between line and plane.
	*	dir = _end - _start;
	*	t = (zPlane - dot(normal, start)) / dot(normal, dir);
	*	intersection = start + dir * t;
	*
	*	Simplifications:
	*	> start == float3(0, 0, 0);
	*	> dir == _end;
	*	> normal == float3(0, 0, 1);
	*	> dot(normal, start) == dot(normal, float3(0, 0, 0)) == 0;
	*	> dot(normal, dir) == dot(normal, _end) == _end.z;
	*
	*	> end.z = 1 / camera.inverseProjection._m33;
	*	> t = zPlane / end.z == zPlane * camera.inverseProjection._m33;
	*/
	
	const float t = _zPlane * camera.inverseProjection._m33;
	
	return float3(_dirXY * t, _zPlane);
}

#endif // SAPPHIRE_RENDER_SHADER_BUILD_LIGHT_CLUSTER_GRID_GUARD
