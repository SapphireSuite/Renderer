// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD
#define SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD

#include <Common/Camera.hlsl>

namespace SA
{
	struct LightClusterInfo
	{
		uint3 gridSize;
	
		/// Formula: numSlice / log(zFar / zNear).
		float clusterScale;
		
		/// Formula: numSlice * log(zNear) / log(zFar / zNear).
		float clusterBias;
	};

	cbuffer LightClusterInfoBuffer : register(b0)
	{
		LightClusterInfo lightClusterInfo;
	};
	
	
	//---------- Helper Functions ----------
	
	float2 ComputeTilePixelSize()
	{
		return camera.screen / float2(lightClusterInfo.gridSize.x, lightClusterInfo.gridSize.y);
	}
}

#endif // SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD
