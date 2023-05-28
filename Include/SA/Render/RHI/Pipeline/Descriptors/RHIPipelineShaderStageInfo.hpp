// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_SHADER_STAGE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_SHADER_STAGE_INFO_GUARD

#include <string>
#include <vector>

#include <Shader/RHIShader.hpp>
#include <Shader/Descriptors/RHIShaderStage.hpp>

namespace SA::RND
{
	namespace RHI
	{
		struct PipelineShaderStageInfo
		{
			/**
			 * Shader code entry point
			 * ex: mainVS
			 */
			std::string entry = "main";
			
			Shader* shader = nullptr;

			ShaderStage stage = ShaderStage::Unknown;
		};

		using PipelineShaderStagesInfo = std::vector<PipelineShaderStageInfo>;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPipelineShaderStageCreateInfo API_GetPipelineShaderStageInfo(const RHI::PipelineShaderStageInfo& _info);
		std::vector<VkPipelineShaderStageCreateInfo> API_GetPipelineShaderStagesInfo(const RHI::PipelineShaderStagesInfo& _info);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_SHADER_STAGE_INFO_GUARD
