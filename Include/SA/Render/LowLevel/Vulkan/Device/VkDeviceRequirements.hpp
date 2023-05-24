// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_REQUIREMENTS_GUARD

#include <vector>

#include <SA/Render/LowLevel/Common/Device/DeviceRequirements.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class WindowSurface;

	struct DeviceRequirements : public RND::DeviceRequirements
	{
	//{ Extensions

		/// \b Vulkan-only required extensions.
		std::vector<const char*> vkRequiredExtensions;

		void AddUniqueExtension(const char* _vkExt);
		bool RemoveExtension(const char* _vkExt);

	//}


	//{ Features
	
		/// Required device features.
		VkPhysicalDeviceFeatures features{};
	
		/// Wether only the required features should be enabled during device creation.
		bool bEnableRequiredFeaturesOnly = false;

	//}


	//{ Window Surface

		WindowSurface* GetWindowSurface() const noexcept;
		void SetWindowSurface(WindowSurface* _winSurface = nullptr, bool bSetPresentQueue = true);

	private:
		/// Window surface required support (if any).
		WindowSurface* mWinSurface = nullptr;
		
	//}
	};
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_REQUIREMENTS_GUARD
