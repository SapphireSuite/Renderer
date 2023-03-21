// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <VkDevice.hpp>

namespace SA::VK
{
	Device::operator VkDevice() const noexcept
	{
		return mLogicalDevice;
	}
	
	Device::operator VkPhysicalDevice() const noexcept
	{
		return mPhysicalDevice;
	}
}
