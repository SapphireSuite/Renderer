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
		SA_LOG_RAII(L"Pipeline destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		SA_VK_API(vkDestroyPipeline(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}


	Pipeline::operator VkPipeline() const noexcept
	{
		return mHandle;
	}
}
