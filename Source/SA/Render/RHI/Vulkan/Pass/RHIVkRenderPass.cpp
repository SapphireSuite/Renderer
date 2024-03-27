// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkRenderPass.hpp>

#include <Device/RHIVkDevice.hpp>

namespace SA::RND::RHI
{
	void VkRenderPass::Create(const Device* _device, const RenderPassInfo& _info)
	{
		mHandle.Create(_device->API_Vulkan(), VK::API_GetRenderPassInfo(_info));
	}

	void VkRenderPass::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}


	void VkRenderPass::Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff)
	{
		mHandle.Begin(_cmd->API_Vulkan(), _fBuff->API_Vulkan());
	}

	void VkRenderPass::NextSubpass(const CommandBuffer* _cmd)
	{
		mHandle.NextSubpass(_cmd->API_Vulkan());
	}

	void VkRenderPass::End(const CommandBuffer* _cmd)
	{
		mHandle.End(_cmd->API_Vulkan());
	}


	const VK::RenderPass& VkRenderPass::API_Vulkan() const
	{
		return mHandle;
	}
}
