// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include "VkDeviceInfo.hpp"
#include "VkDeviceRequirements.hpp"

namespace SA::VK
{
	class Instance;
	class WindowSurface;

	class Device
	{
		/// Logical device handle.
		VkDevice mLogical = VK_NULL_HANDLE;

		/// Physical device handle.
		VkPhysicalDevice mPhysical = VK_NULL_HANDLE;

		/// Physical supported features.
		VkPhysicalDeviceFeatures mFeatures{};
		VkPhysicalDeviceMemoryProperties mMemProperties;

	public:
		const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const noexcept;

		void Create(const DeviceInfo& _info);
		void Destroy();

		void WaitIdle() const;

		static std::vector<DeviceInfo>  QueryDeviceInfos(const Instance& _inst,
			const DeviceRequirements& _reqs = DeviceRequirements{});

		operator VkDevice() const noexcept;
		operator VkPhysicalDevice() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_GUARD
