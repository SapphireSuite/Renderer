// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD
#define SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class CullingMode : uint8_t
		{
			// No culling.
			None,

			// Front-face culling.
			Front,

			// Back-face culling.
			Back,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(RHI::CullingMode _mode);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD
