// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD
#define SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD

#include <Common/Camera.hlsl>

namespace SA
{
#ifndef SA_LIGHT_CLUSTER_INFO_BUFFER_ID
#define SA_LIGHT_CLUSTER_INFO_BUFFER_ID 0
#endif
	
#ifndef SA_LIGHT_CLUSTER_INFO_SET
#define SA_LIGHT_CLUSTER_INFO_SET 0
#endif
	
	struct LightClusterInfo
	{
		uint3 gridSize;
	
		/// Formula: numSlice / log(zFar / zNear).
		float clusterScale;
		
		/// Formula: numSlice * log(zNear) / log(zFar / zNear).
		float clusterBias;
	};

	cbuffer LightClusterInfoBuffer : SA_REG_SPACE(b, SA_LIGHT_CLUSTER_INFO_BUFFER_ID, SA_LIGHT_CLUSTER_INFO_SET)
	{
		LightClusterInfo lightClusterInfo;
	};
	
	
	#define SA_MAX_LIGHT_PER_CLUSTER 63

	struct ClusterLightList
	{
		/// Number of lights in the cluster.
		uint num;
	
		/// Light indices in the cluster.
		uint lightIndices[SA_MAX_LIGHT_PER_CLUSTER];
	};
	
	
	//---------- Helper Functions ----------
	
#if SA_CAMERA_BUFFER

	float2 ComputeTilePixelSize()
	{
		return camera.screen / float2(lightClusterInfo.gridSize.x, lightClusterInfo.gridSize.y);
	}

	
	/**
	*	\brief Get cluster index from pixel position.
	*
	*	\param[in] _pixel Pixel position.
	*
	*	\return Cluster index.
	*/
	uint GetClusterIndex(float3 pixel)
	{
	#if SA_DEPTH_INVERTED
		pixel.z = 1.0f - pixel.z;
	#endif
		
		const uint clusterZSlice = log(pixel.z) * lightClusterInfo.clusterScale - lightClusterInfo.clusterBias;

		const uint2 clusterXY = uint2(pixel.xy / SA::ComputeTilePixelSize());
	
		const uint clusterIndex = clusterXY.x + clusterXY.y * lightClusterInfo.gridSize.x + clusterZSlice * lightClusterInfo.gridSize.x * lightClusterInfo.gridSize.y;

		return clusterIndex;
	}
	
#endif
}

#endif // SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD
