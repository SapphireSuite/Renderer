// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIPass.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	const VK::RenderPass* Pass::API_Vulkan() const
	{
		SA_ASSERT((Default, false), SA.Render.RHI.Vulkan, L"Query Vulkan API handle from non-vulkan object!");

		return nullptr;
	}
#endif
}
