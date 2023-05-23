// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipeline.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void Pipeline::Create(const Device& _device, const VkGraphicsPipelineCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &_vkInfo, nullptr, &mHandle),
			L"Failed to create graphics pipeline");

		SA_LOG(L"Pipeline created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void Pipeline::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyPipeline(_device, mHandle, nullptr));

		SA_LOG(L"Pipeline destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
		
		mHandle = VK_NULL_HANDLE;
	}


	Pipeline::operator VkPipeline() const noexcept
	{
		return mHandle;
	}
}
