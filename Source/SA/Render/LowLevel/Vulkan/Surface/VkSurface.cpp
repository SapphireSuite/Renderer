// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/VkSurface.hpp>

#include <Device/VkDevice.hpp>

#include <Surface/VkWindowSurface.hpp>

namespace SA::VK
{
	void Surface::Create(const Device& _device, const WindowSurface& _winSurface)
	{
		mHandle = _winSurface;
		swapchain.Create(_device, *this);

		SA_LOG(L"Surface created!", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void Surface::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"Surface created!", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		swapchain.Destroy(_device);
		mHandle = VK_NULL_HANDLE;
	}


	SurfaceSupportDetails Surface::QuerySupportDetails(VkPhysicalDevice _device) const
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

	Surface::operator VkSurfaceKHR() const noexcept
	{
		return mHandle;
	}
}
