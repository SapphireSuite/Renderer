// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_SHADER_STAGE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_SHADER_STAGE_INFO_GUARD

#include <string>
#include <vector>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pipeline/Info/D12GraphicsPipelineInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		class Shader;

		struct GraphicsPipelineShaderStageInfo
		{
			/// Vertex Shader.
			Shader* vs = nullptr;
			
			/// Geometry Shader.
			Shader* gs = nullptr;
			
			/// Pixel Shader.
			Shader* ps = nullptr;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			std::vector<VkPipelineShaderStageCreateInfo> API_MakeVkPipelineShaderStagesInfo() const;
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			DX12::GraphicsPipelineShaderStages API_MakeDX12PipelineShaderStages() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_SHADER_STAGE_INFO_GUARD
