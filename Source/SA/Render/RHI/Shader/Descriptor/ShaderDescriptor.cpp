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

	VK::VertexInputStateInfo ShaderDescriptor::MakeVkVertexInputStateInfoSingleVertexBuffer() const
	{
		VK::VertexInputStateInfo info;

		VkVertexInputBindingDescription& bindDesc = info.bindDescs.emplace_back();
		bindDesc.binding = 0;
		bindDesc.stride = 0;
		bindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		for(auto& input : inputs)
		{
			VkVertexInputAttributeDescription& attribDesc = info.attribDescs.emplace_back();
			attribDesc.location = input.location;
			attribDesc.binding = 0;
			attribDesc.format = VK::API_GetFormat(input.format);
			attribDesc.offset = bindDesc.stride;

			bindDesc.stride += input.size;
		}

		return info;
	}

	VK::VertexInputStateInfo ShaderDescriptor::MakeVkVertexInputStateInfoMultipleVertexBuffers() const
	{
		VK::VertexInputStateInfo info;

		for (uint32_t i = 0; i < static_cast<uint32_t>(inputs.size()); ++i)
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

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	std::vector<D3D12_INPUT_ELEMENT_DESC> ShaderDescriptor::MakeDX12VertexInputElementDescs() const
	{
		std::vector<D3D12_INPUT_ELEMENT_DESC> dxDescs;
		dxDescs.reserve(inputs.size());

		for (uint32_t i = 0; i < static_cast<uint32_t>(inputs.size()); ++i)
		{
			auto& input = inputs[i];
			auto& out = dxDescs.emplace_back();

			out.SemanticName = input.semantic.c_str();
			out.SemanticIndex = 0;
			out.Format = DX12::API_GetFormat(input.format);
			out.InputSlot = input.location;
			out.AlignedByteOffset = 0;
			out.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			out.InstanceDataStepRate = 0;
		}

		return dxDescs;
	}

#endif
}
