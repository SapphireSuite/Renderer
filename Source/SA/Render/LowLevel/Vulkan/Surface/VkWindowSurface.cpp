// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/VkWindowSurface.hpp>

#include <VkInstance.hpp>

namespace SA::VK
{
	void WindowSurface::InitializeHandle(VkSurfaceKHR&& _handle)
	{
		mHandle = _handle;

		SA_LOG(L"Window Surface handle initialized.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void WindowSurface::Create(const Instance& _instance, AWindow* _window)
	{
		// TODO: Implement with Sapphire Windowing lib.
		(void)_instance;
		(void)_window;
	}

	void WindowSurface::Destroy(const Instance& _instance)
	{
		vkDestroySurfaceKHR(_instance, mHandle, nullptr);
	}

	SurfaceSupportDetails WindowSurface::QuerySupportDetails(VkPhysicalDevice _device) const
	{
		SurfaceSupportDetails details{};

	//{ KHR Capabilities.

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, mHandle, &details.capabilities);

	//}


	//{ KHR Formats.

		uint32_t formatCount = 0u;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, details.formats.data());
		}

	//}


	//{ KHR Present Modes.
	
		uint32_t presentModeCount = 0u;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, details.presentModes.data());
		}

	//}

		return details;	
	}

	WindowSurface::operator VkSurfaceKHR() const
	{
		return mHandle;
	}	
}
