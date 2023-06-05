// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD

#include "ShaderBindingSetDescriptor.hpp"
#include "ShaderInputDescriptor.hpp"

#include <SA/Render/RHI/Shader/Descriptor/RHIShaderStage.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pipeline/Info/VkPipelineVertexInputStateInfo.hpp>

#endif

namespace SA::RND::RHI
{
	struct ShaderDescriptor
	{
		std::string entrypoint = "main";

		ShaderStage stage = ShaderStage::Unknown;

		std::vector<ShaderInputDescriptor> inputs;
		std::vector<ShaderBindingSetDescriptor> sets;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::PipelineVertexInputStateInfo MakeVkPipelineVertexInputStateInfo() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
