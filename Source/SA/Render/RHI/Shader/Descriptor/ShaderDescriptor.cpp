// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/Descriptor/ShaderDescriptor.hpp>

namespace SA::RND::RHI
{
	ShaderBindingSetDescriptor& ShaderDescriptor::GetOrEmplaceSet(uint32_t _setIndex)
	{
		for (size_t i = sets.size(); i <= _setIndex; ++i)
			sets.emplace_back();

		return sets[_setIndex];
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::VertexInputStateInfo ShaderDescriptor::MakeVkVertexInputStateInfo() const
	{
		VK::VertexInputStateInfo info;

		for(uint32_t i = 0; i < static_cast<uint32_t>(inputs.size()); ++i)
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
