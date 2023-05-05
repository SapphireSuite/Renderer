// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::VK
{
	class WindowSurface
	{
		VkSurfaceKHR mHandle;
	public:

		operator VkSurfaceKHR() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
