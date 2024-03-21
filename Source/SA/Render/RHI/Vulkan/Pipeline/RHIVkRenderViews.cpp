// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIVkRenderViews.hpp>

#include <Device/Command/RHIVkCommandBuffer.hpp>

namespace SA::RND::RHI
{
	void VkRenderViews::AddView(const Rect2Df& _viewport, const Rect2Dui& _scissor)
	{
		// Invert Viewport to flip Y-axis.
		const VkViewport vkViewport{
			.x = _viewport.x,
			.y = _viewport.height,
			.width = _viewport.width,
			.height = -_viewport.height,
			.minDepth = 0.0f,
			.maxDepth = 1.0f,
		};

		const VkRect2D vkScissor{
			.offset { .x = static_cast<int32_t>(_scissor.x), .y = static_cast<int32_t>(_scissor.y) },
			.extent { .width = _scissor.width, .height = _scissor.height },
		};

		mHandle.AddView(vkViewport, vkScissor);
	}

	void VkRenderViews::Bind(const CommandBuffer* _cmd)
	{
		mHandle.Bind(_cmd->API_Vulkan());
	}

	const VK::RenderViews& VkRenderViews::API_Vulkan() const
	{
		return mHandle;
	}
}
