// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_VIEWS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_VIEWS_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class CommandBuffer;

	class RenderViews
	{
	public:
		std::vector<VkViewport> viewports;
		std::vector<VkRect2D> scissors;

		void AddView(const VkViewport& _viewport, const VkRect2D& _scissor);
		void AddFullView(Vec2ui _extents);

		void Bind(const CommandBuffer& _cmd);

		VkPipelineViewportStateCreateInfo MakeVkStateInfo() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_RENDER_VIEWS_GUARD
