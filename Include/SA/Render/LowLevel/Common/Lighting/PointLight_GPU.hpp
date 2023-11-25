// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_POINT_LIGHT_GPU_GUARD
#define SAPPHIRE_RENDER_POINT_LIGHT_GPU_GUARD

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	/**
	* Must match Point Light cbuffer in Lighting.hlsl.
	*/
	struct PointLight_GPU
	{
		Vec3f position;

		Vec3f color;

		float radius = 10.0f;

		float intensity = 1.0f;


	//{ Components

		/// Ambient lighting component.
		float ambient = 0.01f;

		/// Diffuse lighting component.
		float diffuse = 0.64f;

		/// Specular lighting component.
		float specular = 0.35f;

	//}
	};
}

#endif // SAPPHIRE_RENDER_POINT_LIGHT_GPU_GUARD
