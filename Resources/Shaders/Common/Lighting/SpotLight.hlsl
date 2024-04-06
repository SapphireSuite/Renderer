// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD

#include "Preprocessors.hlsl"

namespace SA
{
#ifdef SA_SPOT_LIGHT_BUFFER_ID

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

#endif // SA_SPOT_LIGHT_BUFFER_ID
}

#endif // SAPPHIRE_RENDER_SHADER_SPOT_LIGHT_GUARD
