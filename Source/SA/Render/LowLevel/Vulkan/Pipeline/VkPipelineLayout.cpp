// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipelineLayout.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void PipelineLayout::Create(const Device& _device,
		const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& _setLayoutBindings)
	{
		mDescriptorSetLayouts.reserve(_setLayoutBindings.size());

		for (auto& setLayout : _setLayoutBindings)
		{
			DescriptorSetLayout& descSetLayout = mDescriptorSetLayouts.emplace_back();
			descSetLayout.Create(_device, setLayout);
		}


		VkPipelineLayoutCreateInfo info
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.setLayoutCount = static_cast<uint32_t>(mDescriptorSetLayouts.size()),
			.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(mDescriptorSetLayouts.data()),
			.pushConstantRangeCount = 0,
			.pPushConstantRanges = nullptr,
		};

		SA_VK_API(vkCreatePipelineLayout(_device, &info, nullptr, &mHandle), L"Failed to create pipeline layout");

		SA_LOG(L"PipelineLayout created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void PipelineLayout::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyPipelineLayout(_device, mHandle, nullptr));

		for (auto& descSetLayout : mDescriptorSetLayouts)
			descSetLayout.Destroy(_device);

		SA_LOG(L"PipelineLayout destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
		
		mHandle = VK_NULL_HANDLE;
	}


	PipelineLayout::operator VkPipelineLayout() const noexcept
	{
		return mHandle;
	}
}
