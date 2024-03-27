// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIVkPipeline.hpp>

#include <Device/RHIVkDevice.hpp>
#include <Device/Command/RHIVkCommandBuffer.hpp>

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
