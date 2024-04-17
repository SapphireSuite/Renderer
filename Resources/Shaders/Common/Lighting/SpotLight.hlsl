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

		float intensity;

		float3 direction;

		float range;

		float3 color;

		float cutOff;
	};

	StructuredBuffer<PointLight> spotLights : SA_REG_SPACE(t, SA_SPOT_LIGHT_BUFFER_ID, SA_SPOT_LIGHT_SET);


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
		uint num;
		uint stride;
		spotLights.GetDimensions(num, stride);

		float3 sum = float3(0.0f, 0.0f, 0.0f);

		for(int i = 0; i < num; ++i)
		{
			sum += ComputeSpotLightIllumination(_data, spotLights[i]);
		}

		return sum;
	}
}

#else // SA_SPOT_LIGHT_BUFFER_ID

#define SA_SPOT_LIGHTS 0

#endif // SA_SPOT_LIGHT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD
