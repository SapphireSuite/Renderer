// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkPass.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	const VK::RenderPass* VkPass::API_Vulkan() const
	{
		return &mHandle;
	}
}

#endif
