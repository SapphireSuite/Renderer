// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipelineLayout.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void PipelineLayout::Create(const Device& _device, const VkPipelineLayoutCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreatePipelineLayout(_device, &_vkInfo, nullptr, &mHandle), L"Failed to create pipeline layout");

		SA_LOG(L"PipelineLayout created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void PipelineLayout::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"PipelineLayout destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		SA_VK_API(vkDestroyPipelineLayout(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}


	PipelineLayout::operator VkPipelineLayout() const noexcept
	{
		return mHandle;
	}
}
