// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD

#include "VkSurfaceSupportDetails.hpp"

namespace SA
{
	namespace WND::WHI 
	{
		class Window;
	}

	namespace RND::VK
	{
		class Instance;

		class WindowSurface
		{
			VkSurfaceKHR mHandle;
		
		public:
			void InitializeHandle(VkSurfaceKHR&& _handle);

			void Create(const Instance& _instance, const WND::WHI::Window* _window);
			void Destroy(const Instance& _instance);

			SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;

			operator VkSurfaceKHR() const;
		};
	}
}

#endif // SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
