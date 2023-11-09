// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIVkPipelineLayout.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkPipelineLayout::Create(const Device* _device, const PipelineLayoutDescriptor& _desc)
	{
		mHandle.Create(_device->API_Vulkan(), _desc.API_Vulkan());
	}
	
	void VkPipelineLayout::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	const VK::PipelineLayout& VkPipelineLayout::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
