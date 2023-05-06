// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_SURFACE_GUARD

#include "VkSwapchain.hpp"
#include "VkSurfaceSupportDetails.hpp"

namespace SA::VK
{
	class WindowSurface;

	class Surface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

	public:
		Swapchain swapchain;

		void Create(const Device& _device, const WindowSurface& _winSurface);
		void Destroy(const Device& _device);

		SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;
		
		operator VkSurfaceKHR() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_SURFACE_GUARD
