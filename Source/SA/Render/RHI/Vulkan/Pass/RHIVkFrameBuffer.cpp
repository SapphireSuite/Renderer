// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkFrameBuffer.hpp>

#include <Device/RHIVkDevice.hpp>

namespace SA::RND::RHI
{
	void VkFrameBuffer::Create(const Device* _device, const RenderPass* _pass)
	{
		//mHandle.Create(_device->API_Vulkan(), _pass->API_Vulkan(), _pass->GetInfo().API_Vulkan());
	}
	
	void VkFrameBuffer::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	const VK::FrameBuffer& VkFrameBuffer::API_Vulkan() const
	{
		return mHandle;
	}
}
