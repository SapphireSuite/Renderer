// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD

#include "Preprocessors.hlsl"

namespace SA
{
#ifdef SA_DIRECTIONAL_LIGHT_BUFFER_ID

	struct DirectionalLight
	{
		float3 direction;

		float3 color;

		float intensity;


	//{ Components

		float ambient;

		float diffuse;

		float specular;

	//}
	};

	cbuffer DirectionalLightBuffer : SA_REG_SPACE(b, SA_DIRECTIONAL_LIGHT_BUFFER_ID, 2)
	{
		DirectionalLight directionalLight;
	};

#endif // SA_DIRECTIONAL_LIGHT_BUFFER_ID
}

#endif // SAPPHIRE_RENDER_SHADER_DIRECTIONAL_LIGHT_GUARD
