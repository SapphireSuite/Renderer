// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHIVkSampledTexture.hpp>

#include <Device/RHIVkDevice.hpp>
#include <RHIVkResourceInitializer.hpp>

namespace SA::RND::RHI
{
	void VkSampledTexture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_Vulkan(), _init->API_Vulkan(), _raw);
	}

	void VkSampledTexture::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}
}
