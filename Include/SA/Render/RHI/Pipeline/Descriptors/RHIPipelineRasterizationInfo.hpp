// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_RASTERIZATION_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_RASTERIZATION_INFO_GUARD

#include "RHICullingMode.hpp"
#include "RHIFrontFaceMode.hpp"
#include "RHIPolygonMode.hpp"

namespace SA::RND::RHI
{
	struct PipelineRasterizationInfo
	{
		/// Whether to use conservative rasterization.
		bool bConservative = false;

		/// Whether to enable depth-testing.
		bool bDepthTest = true;

		/// Rasterization polygon mode.
		PolygonMode polygon = PolygonMode::Fill;

		/// Rasterization culling mode.
		CullingMode cullingMode = CullingMode::Back;

		/// Rasterization front face mode.
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkPipelineRasterizationStateCreateInfo API_Vulkan() const;
	
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_RASTERIZATION_INFO_GUARD
