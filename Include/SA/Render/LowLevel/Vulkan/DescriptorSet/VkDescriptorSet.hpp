// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class DescriptorSet
	{
		friend class DescriptorPool;

		VkDescriptorSet mHandle = VK_NULL_HANDLE;
	};

	static_assert(sizeof(DescriptorSet) == sizeof(VkDescriptorSet),
		"DescriptorSet size must match VkDescriptorSet. See utilization in VK::DescriptorPool.");
}

#endif // SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
