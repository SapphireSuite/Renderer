// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD

#include "../Preprocessors.hlsl"
#include "Illumination.hlsl"

#ifdef SA_SPOT_LIGHT_BUFFER_ID

#define SA_SPOT_LIGHTS 1

namespace SA
{
	struct SpotLight
	{
		float3 position;

		float3 direction;

		float3 color;

		float range;

		float intensity;

		float cutOff;
	};

	cbuffer SpotLightBuffer : SA_REG_SPACE(b, SA_SPOT_LIGHT_BUFFER_ID, 2)
	{
		SpotLight spotLights[10];
	};


	//---------- Helper Functions ----------

	float3 ComputeSpotLightIllumination(IlluminationData _data, SpotLight _sLight)
	{
		_data.vLight = _sLight.position - _data.vPosition;
		_data.vnLight = normalize(_data.vLight);


		const float theta = dot(_data.vnLight, normalize(_sLight.direction));

		// Fragment not in spot light.
		if(theta < _sLight.cutOff)
			return float3(0.0f);


		LightData lData;
		lData.color = _sLight.color;
		lData.intensity = _sLight.intensity;
		lData.range = _sLight.radius;
		lData.bAttenuation = true;

		return ComputeBRDF(_data, lData);
	}

	float3 ComputeSpotLightsIllumination(IlluminationData _data)
	{
		float3 sum = float3(0.0f);

		for(int i = 0; i < 10; ++i)
		{
			sum += ComputeSpotLightIllumination(_data, SpotLights[i]);
		}

		return sum;
	}
}

#else // SA_SPOT_LIGHT_BUFFER_ID

#define SA_SPOT_LIGHTS 0

#endif // SA_SPOT_LIGHT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD
