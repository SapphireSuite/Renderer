// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD

#include <SA/Render/LowLevel/Common/Device/RenderDeviceInfo.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::VK
{
	struct DeviceInfo : public RenderDeviceInfo
	{
		/// Physical device handle.
		VkPhysicalDevice physicalDevice;

		/// Physical device's supported features.
		VkPhysicalDeviceFeatures physicalFeatures{};

		/// \b Vulkan-only required extensions.
		std::vector<const char*> vkRequiredExts;

	private:
		friend class Device;

		bool CheckExtensionSupport() const noexcept;

		bool CheckFeatureSupport(const VkPhysicalDeviceFeatures& _vkReqFeatures) const noexcept;

		/// Evaluate device to compute score.
		void Evaluate();
	};
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
