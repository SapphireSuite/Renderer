// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <DescriptorSet/VkDescriptorPool.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void DescriptorPool::Create(const Device& _device, const DescriptorPoolInfos& _info)
	{
		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = _info.setNum;
		descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(_info.poolSizes.size());
		descriptorPoolInfo.pPoolSizes = _info.poolSizes.data();

		SA_VK_API(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mHandle),
			L"Failed to create descriptor pool!");

		SA_LOG(L"Descriptor Pool created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void DescriptorPool::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyDescriptorPool(_device, mHandle, nullptr))

		SA_LOG(L"Descriptor Pool destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		mHandle = VK_NULL_HANDLE;
	}

	
	DescriptorSet DescriptorPool::Allocate(const Device& _device, const DescriptorSetLayout& _layout)
	{
		DescriptorSet set;

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = 1u;
		descriptorSetAllocInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(&_layout);

		SA_VK_API(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, reinterpret_cast<VkDescriptorSet*>(&set)),
			L"Failed to allocate descriptor set!");

		return set;
	}
	
	std::vector<DescriptorSet> DescriptorPool::Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts)
	{
		std::vector<DescriptorSet> sets(_layouts.size());

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = static_cast<uint32_t>(_layouts.size());
		descriptorSetAllocInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(_layouts.data());

		SA_VK_API(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, reinterpret_cast<VkDescriptorSet*>(sets.data())), 
			L"Failed to allocate descriptor set!");

		return sets;
	}

	
	void DescriptorPool::Free(const Device& _device, DescriptorSet& _set)
	{
		vkFreeDescriptorSets(_device, mHandle, 1u, reinterpret_cast<VkDescriptorSet*>(&_set));
	}
	
	void DescriptorPool::Free(const Device& _device, std::vector<DescriptorSet>& _sets)
	{
		vkFreeDescriptorSets(_device, mHandle,
			static_cast<uint32_t>(_sets.size()),
			reinterpret_cast<VkDescriptorSet*>(_sets.data()));
	}
}
