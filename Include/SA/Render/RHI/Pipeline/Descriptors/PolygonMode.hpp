// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_POLYGON_MODE_GUARD
#define SAPPHIRE_RENDER_RHI_POLYGON_MODE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class PolygonMode : uint8_t
		{
			// Draw point only.
			Point,

			// Draw line only.
			Line,

			// Draw fill triangle.
			Fill
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPolygonMode API_GetPolygonMode(RHI::PolygonMode _mode);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_POLYGON_MODE_GUARD
