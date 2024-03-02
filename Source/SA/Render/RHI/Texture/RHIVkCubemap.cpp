// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHIVkCubemap.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkCubemap::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawCubemap& _raw)
	{
		mHandle.Create(_device->API_Vulkan(), _init->API_Vulkan(), _raw);
	}
	
	void VkCubemap::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	const VK::Cubemap& VkCubemap::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif
