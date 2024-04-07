// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD

#include "../Preprocessors.hlsl"
#include "Illumination.hlsl"

#ifdef SA_POINT_LIGHT_BUFFER_ID

#define SA_POINT_LIGHTS 1

namespace SA
{
	struct PointLight
	{
		float3 position;

		float3 color;

		float radius;

		float intensity;
	};

	cbuffer PointLightBuffer : SA_REG_SPACE(b, SA_POINT_LIGHT_BUFFER_ID, 2)
	{
		PointLight pointLights[10];
	};


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

	float3 ComputePointLightsIllumination(IlluminationData _data)
	{
		float3 sum = float3(0.0f);

		for(int i = 0; i < 10; ++i)
		{
			sum += ComputePointLightIllumination(_data, pointLights[i]);
		}

		return sum;
	}
}

#else // SA_POINT_LIGHT_BUFFER_ID

#define SA_POINT_LIGHTS 0

#endif // SA_POINT_LIGHT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
