// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD

#include "../Preprocessors.hlsl"
#include "Illumination.hlsl"
#include <Passes/LightCulling/LightClusterCommon.hlsl>

#ifdef SA_POINT_LIGHT_BUFFER_ID

#define SA_POINT_LIGHTS 1

namespace SA
{
	struct PointLight
	{
		float3 position;

		float intensity;

		float3 color;

		float radius;
	};

	StructuredBuffer<PointLight> pointLights : SA_REG_SPACE(t, SA_POINT_LIGHT_BUFFER_ID, SA_POINT_LIGHT_SET);


//{ Culling

	#ifdef SA_CULLED_POINT_LIGHT_GRID_BUFFER_ID

		#define SA_POINT_LIGHT_CULLING 1

		StructuredBuffer<ClusterLightList> culledPointLightGrid : SA_REG_SPACE(t, SA_CULLED_POINT_LIGHT_GRID_BUFFER_ID, SA_POINT_LIGHT_SET);

	#else

		#define SA_POINT_LIGHT_CULLING 0

	#endif

//}


	//---------- Helper Functions ----------

	float3 ComputePointLightIllumination(IlluminationData _data, PointLight _pLight)
	{
		_data.vLight = _pLight.position - _data.vPosition;
		_data.vnLight = normalize(_data.vLight);

		LightData lData;
		lData.color = _pLight.color;
		lData.intensity = _pLight.intensity;
		lData.range = _pLight.radius;
		lData.bAttenuation = true;

		return ComputeBRDF(_data, lData);
	}

	#if SA_POINT_LIGHT_CULLING
	
	float3 ComputePointLightsIllumination(float3 _vsPosition, IlluminationData _data)
	{
		float3 sum = float3(0.0f, 0.0f, 0.0f);

		uint num;
		uint stride;
		pointLights.GetDimensions(num, stride);

		const uint clusterIndex = ComputeLightClusterIndex(_vsPosition);

		const ClusterLightList cluster = culledPointLightGrid[clusterIndex];

		for(int i = 0; i < cluster.num; ++i)
		{
			sum += ComputePointLightIllumination(_data, pointLights[cluster.lightIndices[i]]);
		}

		return sum;
	}

	#else

	float3 ComputePointLightsIllumination(IlluminationData _data)
	{
		float3 sum = float3(0.0f, 0.0f, 0.0f);

		uint num;
		uint stride;
		pointLights.GetDimensions(num, stride);

		for(int i = 0; i < num; ++i)
		{
			sum += ComputePointLightIllumination(_data, pointLights[i]);
		}

		return sum;
	}

	#endif
}

#else // SA_POINT_LIGHT_BUFFER_ID

#define SA_POINT_LIGHTS 0

#endif // SA_POINT_LIGHT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
