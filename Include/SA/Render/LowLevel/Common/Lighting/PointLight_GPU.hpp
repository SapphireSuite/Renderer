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

		/// Intensity in Candelas.
		float intensity = 1.0f;

		Vec3f color;

		float radius = 10.0f;
	};
}

#endif // SAPPHIRE_RENDER_POINT_LIGHT_GPU_GUARD
