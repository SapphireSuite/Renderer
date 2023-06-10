// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_VERTEX_INPUT_STATE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_VERTEX_INPUT_STATE_INFO_GUARD

#include <vector>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct VertexInputStateInfo
	{
		std::vector<VkVertexInputBindingDescription> bindDescs;

		std::vector<VkVertexInputAttributeDescription> attribDescs;

		VkPipelineVertexInputStateCreateInfo MakeVkInfo() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_VERTEX_INPUT_STATE_INFO_GUARD
