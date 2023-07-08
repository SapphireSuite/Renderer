// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/VkVertexInputStateInfo.hpp>

namespace SA::RND::VK
{
	VkPipelineVertexInputStateCreateInfo VertexInputStateInfo::MakeVkInfo() const
	{
		return VkPipelineVertexInputStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.vertexBindingDescriptionCount = static_cast<uint32_t>(bindDescs.size()),
			.pVertexBindingDescriptions = bindDescs.data(),
			.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribDescs.size()),
			.pVertexAttributeDescriptions = attribDescs.data()
		};
	}
}
