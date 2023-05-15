// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkPass.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkPass::Create(const Device* _device, const PassDescriptor& _desc)
	{
		mHandle.Create(*_device->API_Vulkan(), VK::API_MakeRenderPassDescriptor(_desc));
	}

	void VkPass::Destroy(const Device* _device)
	{
		mHandle.Destroy(*_device->API_Vulkan());
	}


	const VK::RenderPass* VkPass::API_Vulkan() const
	{
		return &mHandle;
	}
}

#endif
