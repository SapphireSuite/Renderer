// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <DescriptorSet/VkDescriptorSetLayout.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void DescriptorSetLayout::Create(const Device& _device, const std::vector<VkDescriptorSetLayoutBinding>& _setLayoutBindings)
	{
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.bindingCount = static_cast<uint32_t>(_setLayoutBindings.size()),
			.pBindings = _setLayoutBindings.data()
		};

		SA_VK_API(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &mHandle),
			L"Failed to create descriptor set layout");

		SA_LOG(L"DescriptorSetLayout created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void DescriptorSetLayout::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyDescriptorSetLayout(_device, mHandle, nullptr));

		SA_LOG(L"DescriptorSetLayout destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		mHandle = VK_NULL_HANDLE;
	}


	DescriptorSetLayout::operator VkDescriptorSetLayout() const noexcept
	{
		return mHandle;
	}
}
