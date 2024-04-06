// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPOT_LIGHT_GPU_GUARD
#define SAPPHIRE_RENDER_SPOT_LIGHT_GPU_GUARD

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	/**
	* Must match Spot Light cbuffer in Lighting.hlsl.
	*/
	struct SpotLight_GPU
	{
		Vec3f position;

		Vec3f direction;

		Vec3f color;

		float range = 10.0f;

		/// Intensity in Candelas.
		float intensity = 1.0f;

		float cutOff = 60.0f;
	};
}

#endif // SAPPHIRE_RENDER_SPOT_LIGHT_GPU_GUARD
