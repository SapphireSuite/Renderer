// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHIVkRenderTarget.hpp>

#include <Device/RHIVkDevice.hpp>

namespace SA::RND::RHI
{
	void VkRenderTarget::Create(const Device* _device, const RenderTargetDescriptor& _desc)
	{
		mHandle.Create(_device->API_Vulkan(), _desc.API_Vulkan());
	}

	void VkRenderTarget::CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex)
	{
		mHandle.CreateFromImage(_swapchain->API_Vulkan(), _imageIndex);
	}

	void VkRenderTarget::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}
}
