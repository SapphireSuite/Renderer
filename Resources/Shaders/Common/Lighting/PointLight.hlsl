// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
#define SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD

#include "Preprocessors.hlsl"

namespace SA
{
#ifdef SA_POINT_LIGHT_BUFFER_ID

	struct PointLight
	{
		float3 position;

		float3 color;

		float radius;

		float intensity;


	//{ Components

		float ambient;

		float diffuse;

		float specular;

	//}
	};

	cbuffer PointLightBuffer : SA_REG_SPACE(b, SA_POINT_LIGHT_BUFFER_ID, 2)
	{
		PointLight pointLights[10];
	};

#endif // SA_POINT_LIGHT_BUFFER_ID
}

#endif // SAPPHIRE_RENDER_SHADER_POINT_LIGHT_GUARD
