// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD

#include "RHIShaderStage.hpp"
#include "ShaderBindingSetDescriptor.hpp"
#include "ShaderInputDescriptor.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pipeline/Info/VkVertexInputStateInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#endif

namespace SA::RND::RHI
{
	struct ShaderDescriptor
	{
		std::string entrypoint = "main";

		ShaderStage stage = ShaderStage::Unknown;

		std::vector<ShaderInputDescriptor> inputs;
		std::vector<ShaderBindingSetDescriptor> sets;

		ShaderBindingSetDescriptor& GetOrEmplaceSet(uint32_t _setIndex);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::VertexInputStateInfo MakeVkVertexInputStateInfo() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		std::vector<D3D12_INPUT_ELEMENT_DESC> MakeDX12VertexInputElementDescs() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
