// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_POOL_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_POOL_GUARD

#include "VkDescriptorSet.hpp"
#include "VkDescriptorSetLayout.hpp"

namespace SA::RND::VK
{
	struct DescriptorPoolInfos
	{
		uint32_t setNum = 1u;
		std::vector<VkDescriptorPoolSize> poolSizes;
	};

	class DescriptorPool
	{
		VkDescriptorPool mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const DescriptorPoolInfos& _info);
		void Destroy(const Device& _device);

		DescriptorSet Allocate(const Device& _device, const DescriptorSetLayout& _layout);
		std::vector<DescriptorSet> Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts);

		void Free(const Device& _device, DescriptorSet& _set);
		void Free(const Device& _device, std::vector<DescriptorSet>& _sets);
	};
}

#endif // SAPPHIRE_RENDER_VK_DESCRIPTOR_POOL_GUARD
