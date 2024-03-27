// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include "PipelineBindingDescriptor.hpp"

namespace SA::RND::RHI
{
	struct PipelineBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<PipelineBindingDescriptor> bindings;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		std::vector<VkDescriptorSetLayoutBinding> API_Vulkan() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD
