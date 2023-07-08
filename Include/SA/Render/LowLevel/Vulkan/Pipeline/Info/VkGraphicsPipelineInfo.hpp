// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GRAPHICS_PIPELINE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_GRAPHICS_PIPELINE_INFO_GUARD

#include "VkVertexInputStateInfo.hpp"

namespace SA::RND::VK
{
	class RenderPass;
	class PipelineLayout;
	class RenderViews;

	struct GraphicsPipelineInfo
	{
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		VertexInputStateInfo vertexInputState;

		VkPipelineRasterizationStateCreateInfo raster;
		VkPipelineMultisampleStateCreateInfo multisampling;

		VkPipelineDepthStencilStateCreateInfo depthStencil;

		const PipelineLayout* layout = nullptr;

		const RenderPass* renderPass = nullptr;
		uint32_t subpassIndex = 0;

		const RenderViews* views = nullptr;
	};
}

#endif // SAPPHIRE_RENDER_VK_GRAPHICS_PIPELINE_INFO_GUARD
