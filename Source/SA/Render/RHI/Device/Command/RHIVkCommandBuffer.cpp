// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHIVkCommandBuffer.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	const VK::CommandBuffer& VkCommandBuffer::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
