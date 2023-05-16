// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIVkContext.hpp>

#include <Pass/RHIVkPass.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	Pass* VkContext::InstantiatePassClass()
	{
		return new VkPass();
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
