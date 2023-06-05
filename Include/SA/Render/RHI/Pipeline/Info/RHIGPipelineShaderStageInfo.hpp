// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_GPIPELINE_SHADER_STAGE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_GPIPELINE_SHADER_STAGE_INFO_GUARD

#include <string>
#include <vector>

#include <Shader/RHIShader.hpp>

namespace SA::RND
{
	namespace RHI
	{
		struct GPipelineShaderStageInfo
		{
			/// Vertex Shader.
			Shader* vs = nullptr;
			
			/// Geometry Shader.
			Shader* gs = nullptr;
			
			/// Pixel Shader.
			Shader* ps = nullptr;
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPipelineShaderStageCreateInfo API_GetPipelineShaderStageInfo(const RHI::Shader* _shader);
		std::vector<VkPipelineShaderStageCreateInfo> API_GetPipelineShaderStagesInfo(const RHI::GPipelineShaderStageInfo& _info);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_GPIPELINE_SHADER_STAGE_INFO_GUARD
