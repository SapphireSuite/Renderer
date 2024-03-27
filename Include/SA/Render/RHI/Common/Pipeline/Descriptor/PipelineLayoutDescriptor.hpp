// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_LAYOUT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_LAYOUT_DESCRIPTOR_GUARD

#include "PipelineBindingSetDescriptor.hpp"

namespace SA::RND::RHI
{
	struct ShaderDescriptor;

	struct PipelineLayoutDescriptor
	{
		std::vector<PipelineBindingSetDescriptor> sets;

		void AddShader(const ShaderDescriptor& _desc);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		std::vector<std::vector<VkDescriptorSetLayoutBinding>> API_Vulkan() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_LAYOUT_DESCRIPTOR_GUARD
