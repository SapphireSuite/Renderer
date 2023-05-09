// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD

#include <vector>
#include <list>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct RenderPassInfo
	{
		std::vector<VkSubpassDescription> subpassDescriptions;
		std::vector<VkSubpassDependency> subpassDependencies;

		std::vector<VkAttachmentDescription> subpassAttachments;
		std::vector<VkAttachmentReference> subpassDepthAttachmentRefs;
		std::vector<std::vector<VkAttachmentReference>> subpassColorAttachmentRefs;
		std::vector<std::vector<VkAttachmentReference>> subpassAttachmentResolveRefs;
		std::vector<std::vector<VkAttachmentReference>> subpassInputAttachmentRefs;
	};
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
