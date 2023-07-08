// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIPass.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	const PassInfo& Pass::GetInfo() const
	{
		return mPassInfo;
	}

	void Pass::Create(const Device* _device, PassInfo _info)
	{
		(void)_device;
		
		mPassInfo = std::move(_info);
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::RenderPass& Pass::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif
}
