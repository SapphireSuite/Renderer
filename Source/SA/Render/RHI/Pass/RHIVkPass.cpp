// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkPass.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkPass::Create(const Device* _device, const PassInfo& _info)
	{
		mHandle.Create(_device->API_Vulkan(), _info.API_Vulkan());
	}

	void VkPass::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}


	const VK::RenderPass* VkPass::API_Vulkan() const
	{
		return &mHandle;
	}
}

#endif
