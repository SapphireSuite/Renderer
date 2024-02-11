// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIRenderPass.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	const RenderPassInfo& RenderPass::GetInfo() const
	{
		return mPassInfo;
	}

	void RenderPass::Create(const Device* _device, RenderPassInfo _info)
	{
		(void)_device;
		
		mPassInfo = std::move(_info);
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::RenderPass& RenderPass::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif
}
