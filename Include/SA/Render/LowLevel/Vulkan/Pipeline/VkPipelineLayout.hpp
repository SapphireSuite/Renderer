// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD

#include <vector>

#include <SA/Render/LowLevel/Vulkan/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace SA::RND::VK
{
	class Device;

	class PipelineLayout
	{
		VkPipelineLayout mHandle = VK_NULL_HANDLE;

		std::vector<DescriptorSetLayout> mDescriptorSetLayouts;

	public:
		void Create(const Device& _device, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& _setLayoutBindings);
		void Destroy(const Device& _device);

		operator VkPipelineLayout() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD
