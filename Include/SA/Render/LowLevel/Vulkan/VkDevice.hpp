// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_GUARD

#include "VulkanAPI.hpp"

namespace SA
{
	namespace VK
	{
		class Device
		{
			VkDevice mLogicalDevice = VK_NULL_HANDLE;
			VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;

		public:
			operator VkDevice() const noexcept;
			operator VkPhysicalDevice() const noexcept;
		};
	}
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_GUARD
