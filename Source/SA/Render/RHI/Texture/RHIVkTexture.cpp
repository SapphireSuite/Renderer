// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHIVkTexture.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkTexture::Create(const Device* _device, const SA::RND::TextureDescriptor& _desc)
	{
		mHandle.Create(_device->API_Vulkan(), _desc);
	}

	void VkTexture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_Vulkan(), _init->API_Vulkan(), _raw);
	}
	
	void VkTexture::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	const VK::Texture& VkTexture::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif
