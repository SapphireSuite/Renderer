// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_DEPTH_STENCIL_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_DEPTH_STENCIL_INFO_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
#include <SA/Render/LowLevel/DX12/DX12API.hpp>
#endif

namespace SA::RND::RHI
{
	enum class DepthTestingMethod
	{
		Default = 0,
		
		Inverse = 1,
	};

	struct GraphicsPipelineDepthStencilInfo
	{
		/// Enable depth testing.
		bool bDepthTest = true;

		/// Enable write into depth buffer.
		bool bDepthWrite = true;

		bool bStencilTest = false;

		DepthTestingMethod method = DepthTestingMethod::Default;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		VkPipelineDepthStencilStateCreateInfo API_Vulkan() const;
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
		D3D12_DEPTH_STENCIL_DESC API_DirectX12() const;
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_DEPTH_STENCIL_INFO_GUARD
