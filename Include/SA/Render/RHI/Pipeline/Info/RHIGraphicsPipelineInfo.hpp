// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_INFO_GUARD

#include "RHIGraphicsPipelineRasterizationInfo.hpp"
#include "RHIGraphicsPipelineShaderStageInfo.hpp"
#include "RHIGraphicsPipelineDepthStencilInfo.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		struct GraphicsPipelineInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		struct GraphicsPipelineInfo;
	}

#endif

	namespace RHI
	{
		class Pass;
		class PipelineLayout;
		class RenderViews;

		struct GraphicsPipelineInfo
		{
			GraphicsPipelineShaderStageInfo shaders;
			GraphicsPipelineRasterizationInfo raster;

			GraphicsPipelineDepthStencilInfo depthStencil;

			const PipelineLayout* layout = nullptr;

			const Pass* pass = nullptr;
			uint32_t subpassIndex = 0u;

			const RenderViews* views = nullptr;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
			VK::GraphicsPipelineInfo API_Vulkan() const;
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
			DX12::GraphicsPipelineInfo API_DirectX12() const;
#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_INFO_GUARD
