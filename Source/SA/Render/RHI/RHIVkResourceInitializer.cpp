// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIVkResourceInitializer.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkResourceInitializer::Create(const Device* _device)
	{
		mHandle.Create(_device->API_Vulkan());
	}

	void VkResourceInitializer::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}


	VK::ResourceInitializer& VkResourceInitializer::API_Vulkan()
	{
		return mHandle;
	}
}

#endif
