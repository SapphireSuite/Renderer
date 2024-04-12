// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DIRECTIONAL_LIGHT_GPU_GUARD
#define SAPPHIRE_RENDER_DIRECTIONAL_LIGHT_GPU_GUARD

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	/**
	* Must match Directional Light cbuffer in DirectionalLight.hlsl.
	*/
	struct DirectionalLight_GPU
	{
		Vec3f direction = Vec3f::Forward;

		/// Intensity in Candelas.
		float intensity = 1.0f;

		Vec3f color = Vec3f::One;

		float padding = 0.0f;
	};
}

#endif // SAPPHIRE_RENDER_DIRECTIONAL_LIGHT_GPU_GUARD
