// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SURFACE_SUPPORT_DETAILS_GUARD
#define SAPPHIRE_RENDER_VK_SURFACE_SUPPORT_DETAILS_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct SurfaceSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat() const;
		VkPresentModeKHR ChooseSwapPresentMode() const;
		Vec2ui ChooseSwapExtent() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_SURFACE_SUPPORT_DETAILS_GUARD
