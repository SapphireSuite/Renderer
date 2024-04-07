// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD

#include "../Preprocessors.hlsl"
#include "Illumination.hlsl"

#ifdef SA_DIRECTIONAL_LIGHT_BUFFER_ID

#define SA_DIRECTIONAL_LIGHTS 1

namespace SA
{
	struct DirectionalLight
	{
		float3 direction;

		float3 color;

		float intensity;
	};

	cbuffer DirectionalLightBuffer : SA_REG_SPACE(b, SA_DIRECTIONAL_LIGHT_BUFFER_ID, 2)
	{
		DirectionalLight directionalLight;
	};


	//---------- Helper Functions ----------

	float3 ComputeDirectionalLightIllumination(IlluminationData _data, DirectionalLight _dLight)
	{
		_data.vnLight = normalize(-_dLight.direction);

		LightData lData;
		lData.color = _dLight.color;
		lData.intensity = _dLight.intensity;
		lData.bAttenuation = false;

		return ComputeBRDF(_data, lData);
	}

	float3 ComputeDirectionalLightsIllumination(IlluminationData _data)
	{
		float3 sum = float3(0.0f);

		for(int i = 0; i < 1; ++i)
		{
			sum += ComputeDirectionalLightIllumination(_data, directionalLight/*s[i]*/);
		}

		return sum;
	}
}

#else // SA_DIRECTIONAL_LIGHT_BUFFER_ID

#define SA_DIRECTIONAL_LIGHTS 0

#endif // SA_DIRECTIONAL_LIGHT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD
