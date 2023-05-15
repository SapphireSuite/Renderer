// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_INSTANCE_GUARD
#define SAPPHIRE_RENDER_VK_INSTANCE_GUARD

#include <vector>

#include "VulkanAPI.hpp"

#include "Device/VkDeviceInfo.hpp"
#include "Device/VkDeviceRequirements.hpp"

namespace SA::RND::VK
{
	class WindowSurface;
	
	class Instance
	{
		VkInstance mHandle = VK_NULL_HANDLE;

	#if SA_VK_VALIDATION_LAYERS

		VkDebugUtilsMessengerEXT mDebugMessenger = nullptr;

	#endif

	public:
		/**
		 * @brief Create the Vulkan instance.
		 * 
		 * @param _vkExtensions \b Vulkan-only required extensions.
		 */
		void Create(std::vector<const char*> _vkExtensions = std::vector<const char*>());

		/**
		 * @brief Destroy the Vulkan instance.
		 */
		void Destroy();

		std::vector<DeviceInfo> QueryDeviceInfos(const DeviceRequirements& _reqs = DeviceRequirements{}) const;

		operator VkInstance() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_INSTANCE_GUARD
