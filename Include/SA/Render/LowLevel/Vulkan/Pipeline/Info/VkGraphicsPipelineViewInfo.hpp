// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_VIEW_INFO_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_VIEW_INFO_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct GraphicsPipelineViewInfo
	{
		std::vector<VkViewport> viewports;
		std::vector<VkRect2D> scissors;

		inline void AddFullViewport(Vec2ui _extents)
		{
			viewports.emplace_back(VkViewport{
				.x = 0.0f,
				.y = 0.0f,
				.width = float(_extents.x),
				.height = float(_extents.y),
				.minDepth = 0.0f,
				.maxDepth = 1.0f
			});

			scissors.emplace_back(VkRect2D{
				.offset { .x = 0, .y = 0 },
				.extent { .width = _extents.x, .height = _extents.y }
			});
		}
	};
}

#endif // SAPPHIRE_RENDER_VK_PIPELINE_VIEW_INFO_GUARD
