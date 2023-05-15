// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIVkDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	// void VkDevice::Create(const DeviceInfo* _info)
	// {
	// }
	
	// void VkDevice::Destroy()
	// {
	// }


	const VK::Device* VkDevice::API_Vulkan() const
	{
		return &mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
