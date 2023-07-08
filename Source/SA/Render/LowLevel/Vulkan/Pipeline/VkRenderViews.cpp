// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkRenderViews.hpp>

#include <Device/Command/VkCommandBuffer.hpp>

namespace SA::RND::VK
{
	void RenderViews::AddView(const VkViewport& _viewport, const VkRect2D& _scissor)
	{
		viewports.emplace_back(_viewport);
		scissors.emplace_back(_scissor);
	}

	void RenderViews::AddFullView(Vec2ui _extents)
	{
		viewports.emplace_back(VkViewport{
			.x = 0,
			.y = 0,
			.width = float(_extents.x),
			.height = float(_extents.y),
			.minDepth = 0.0,
			.maxDepth = 1.0
		});

		scissors.emplace_back(VkRect2D{
			.offset { .x = 0, .y = 0 },
			.extent { .width = _extents.x, .height = _extents.y }
		});
	}

	void RenderViews::Bind(const CommandBuffer& _cmd)
	{
		SA_VK_API(vkCmdSetViewport(_cmd, 0u, static_cast<uint32_t>(viewports.size()), viewports.data()));
		SA_VK_API(vkCmdSetScissor(_cmd, 0u, static_cast<uint32_t>(scissors.size()), scissors.data()));
	}

	VkPipelineViewportStateCreateInfo RenderViews::MakeVkStateInfo() const
	{
		return VkPipelineViewportStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.viewportCount = static_cast<uint32_t>(viewports.size()),
			.pViewports = viewports.data(),
			.scissorCount = static_cast<uint32_t>(scissors.size()),
			.pScissors = scissors.data(),
		};
	}
}
