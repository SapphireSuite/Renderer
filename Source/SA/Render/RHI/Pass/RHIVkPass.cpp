// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkPass.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkPass::Create(const Device* _device, PassInfo _info)
	{
		Pass::Create(_device, std::move(_info));

		mHandle.Create(_device->API_Vulkan(), mInfo.API_Vulkan());
	}
	
	void VkPass::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}


	const VK::RenderPass& VkPass::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
