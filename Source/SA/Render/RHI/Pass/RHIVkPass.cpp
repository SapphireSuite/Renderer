// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkPass.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkPass::Create(const Device* _device, PassInfo _info)
	{
		Pass::Create(_device, std::move(_info));

		mHandle.Create(_device->API_Vulkan(), mPassInfo.API_Vulkan());
	}
	
	void VkPass::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	void VkPass::Begin(const CommandBuffer* _cmd, const FrameBuffer* _fBuff)
	{
		mHandle.Begin(_cmd->API_Vulkan(), _fBuff->API_Vulkan());
	}
	
	void VkPass::NextSubpass(const CommandBuffer* _cmd)
	{
		mHandle.NextSubpass(_cmd->API_Vulkan());
	}
	
	void VkPass::End(const CommandBuffer* _cmd)
	{
		mHandle.End(_cmd->API_Vulkan());
	}


	const VK::RenderPass& VkPass::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
