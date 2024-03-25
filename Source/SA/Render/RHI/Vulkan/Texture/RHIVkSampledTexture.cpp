// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHIVkTexture.hpp>

#include <Device/RHIVkDevice.hpp>
#include <RHIVkResourceInitializer.hpp>

namespace SA::RND::RHI
{
	void VkTexture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_Vulkan(), _init->API_Vulkan(), _raw);
	}

	void VkTexture::Create(const Device* _device, const TextureDescriptor& _desc)
	{
		mHandle.Create(_device->API_Vulkan(), _desc.API_Vulkan());
	}

	void VkTexture::CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex)
	{
		mHandle.CreateFromImage(_swapchain->API_Vulkan(), _imageIndex);
	}

	void VkTexture::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}
}
