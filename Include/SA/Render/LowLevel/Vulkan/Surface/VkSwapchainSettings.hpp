// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SWAPCHAIN_SETTINGS_GUARD
#define SAPPHIRE_RENDER_VK_SWAPCHAIN_SETTINGS_GUARD

#include <SA/Render/LowLevel/Common/Surface/SwapchainSettingsBase.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct SwapchainSettings : public SwapchainSettingsBase
	{
		/**
		* Override format.
		* Default is defined by WindowSurface.
		*/
		VkFormat format = VK_FORMAT_UNDEFINED;
	};
}

#endif // SAPPHIRE_RENDER_VK_SWAPCHAIN_SETTINGS_GUARD
