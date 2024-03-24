// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Common/Misc/RHIFormat.hpp>
#include <SA/Render/RHI/Common/Misc/RHISampling.hpp>

namespace SA::RND::RHI
{
	struct RenderTargetDescriptor
	{
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		Format format = Format::R8G8B8A8_UNORM;

		Sampling sampling = Sampling::S1Bit;

		Color clearColor = Color{ 0.0f, 0.0f, 0.015f, 0.0f };
	};
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD
