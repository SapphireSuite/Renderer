// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIRenderPass.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::RenderPass& RenderPass::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif
}
