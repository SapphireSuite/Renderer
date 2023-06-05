// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/Descriptor/ShaderDescriptor.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::PipelineVertexInputStateInfo ShaderDescriptor::MakeVkPipelineVertexInputStateInfo() const
	{
		VK::PipelineVertexInputStateInfo info;

		for(size_t i = 0; i < inputs.size(); ++i)
		{
			auto& input = inputs[i];
	
			VkVertexInputBindingDescription& bindDesc = info.bindDescs.emplace_back();
			bindDesc.binding = i;
			bindDesc.stride = input.size;
			bindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			VkVertexInputAttributeDescription& attribDesc = info.attribDescs.emplace_back();
			attribDesc.location = input.location;
			attribDesc.binding = i;
			attribDesc.format = VK::API_GetFormat(input.format);
			attribDesc.offset = 0u;
		}

		return info;
	}

#endif
}
