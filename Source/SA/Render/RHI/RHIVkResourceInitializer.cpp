// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIVkResourceInitializer.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkResourceInitializer::Create(const Device* _device)
	{
		ResourceInitializer::Create(_device);

		mHandle.Create(_device->API_Vulkan());
	}

	void VkResourceInitializer::Destroy()
	{
		mHandle.Destroy(mDevice->API_Vulkan());

		ResourceInitializer::Destroy();
	}

	void VkResourceInitializer::Submit()
	{
		mHandle.Submit(mDevice->API_Vulkan());
	}


	VK::ResourceInitializer& VkResourceInitializer::API_Vulkan()
	{
		return mHandle;
	}
}

#endif
