// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHIVkCommandBuffer.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkCommandBuffer::Begin()
	{
		mHandle.Begin();
	}

	void VkCommandBuffer::End()
	{
		mHandle.End();
	}


	void VkCommandBuffer::Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance)
	{
		mHandle.Draw(_vertexNum, _instanceNum, _firstVertex, _firstInstance);
	}


	VK::CommandBuffer& VkCommandBuffer::API_Vulkan()
	{
		return mHandle;
	}

	const VK::CommandBuffer& VkCommandBuffer::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
