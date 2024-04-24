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

	float2 ComputeLightClusterTilePixelSize()
	{
		return camera.screen / float2(lightClusterInfo.gridSize.x, lightClusterInfo.gridSize.y);
	}

	/**
	*	\brief Compute cluster index from view-space position.
	*
	*	\param[in] _vsPosition View-space position.
	*/
	uint ComputeLightClusterIndex(float3 _vsPosition)
	{
	//{ Compute Grid slice
	
		const uint clusterZSlice = log(_vsPosition.z) * lightClusterInfo.clusterScale - lightClusterInfo.clusterBias;
	
		const float clusterFar = camera.zNear * pow(camera.zFar / camera.zNear, (clusterZSlice + 1) / float(lightClusterInfo.gridSize.z));

		const float2 clusterSliceExtent = float2(clusterFar * camera.inverseProjection._m00, clusterFar * camera.inverseProjection._m11);
		const float2 clusterSliceRange = 2 * clusterSliceExtent;
		
		const float2 clusterSliceSize = clusterSliceRange / float2(lightClusterInfo.gridSize.x, lightClusterInfo.gridSize.y);

	//}
	
	
	//{ Compute Current Cluster Index
	
		const uint clusterXSlice = (_vsPosition.x + clusterSliceExtent.x) / clusterSliceSize.x;
		const uint clusterYSlice = lightClusterInfo.gridSize.y - (_vsPosition.y + clusterSliceExtent.y) / clusterSliceSize.y;
	
		const uint clusterIndex = clusterXSlice + clusterYSlice * lightClusterInfo.gridSize.x + clusterZSlice * lightClusterInfo.gridSize.x * lightClusterInfo.gridSize.y;
	
	//}
	
		return clusterIndex;
	}
	
#endif
}

#endif // SAPPHIRE_RENDER_SHADER_LIGHT_CLUSTER_COMMON_GUARD
