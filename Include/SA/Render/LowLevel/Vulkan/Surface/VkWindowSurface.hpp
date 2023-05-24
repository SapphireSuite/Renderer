// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD

#include "VkSurfaceSupportDetails.hpp"

namespace SA
{
	namespace RND::VK
	{
		class Instance;

		class WindowSurface
		{
			VkSurfaceKHR mHandle = VK_NULL_HANDLE;
		
		public:
			void Create(VkSurfaceKHR&& _handle);
			void Destroy(const Instance& _instance);

			SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;

			operator VkSurfaceKHR() const;
		};
	}
}

#endif // SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
