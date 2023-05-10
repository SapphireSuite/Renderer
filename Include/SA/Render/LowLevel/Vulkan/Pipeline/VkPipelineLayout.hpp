// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class Device;

	class PipelineLayout
	{
		VkPipelineLayout mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const VkPipelineLayoutCreateInfo& _vkInfo);
		void Destroy(const Device& _device);

		operator VkPipelineLayout() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD
