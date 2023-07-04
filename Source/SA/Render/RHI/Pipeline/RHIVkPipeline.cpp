// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIVkPipeline.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

#include <Device/Command/RHICommandBuffer.hpp>

namespace SA::RND::RHI
{
	void VkPipeline::Create(const Device* _device, const GraphicsPipelineInfo& _info)
	{
		mHandle.Create(_device->API_Vulkan(), _info.API_Vulkan());
	}
	
	void VkPipeline::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	void VkPipeline::Bind(const CommandBuffer* _cmd)
	{
		mHandle.Bind(_cmd->API_Vulkan());
	}
	
	const VK::Pipeline& VkPipeline::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
