// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineDepthStencilInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkPipelineDepthStencilStateCreateInfo GraphicsPipelineDepthStencilInfo::API_Vulkan() const
	{
		VkPipelineDepthStencilStateCreateInfo vkInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,

			.depthTestEnable = bDepthTest,
			.depthWriteEnable = bDepthWrite,

			.depthBoundsTestEnable = VK_FALSE,
			.stencilTestEnable = bStencilTest,

			.front = {},
			.back = {},

			.minDepthBounds = 0.0f,
			.maxDepthBounds = 1.0f,
		};

		switch (method)
		{
			case DepthTestingMethod::Default:
			{
				vkInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
				break;
			}
			case DepthTestingMethod::Inverse:
			{
				vkInfo.depthCompareOp = VK_COMPARE_OP_GREATER_OR_EQUAL;
				break;
			}
		}

		return vkInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	D3D12_DEPTH_STENCIL_DESC GraphicsPipelineDepthStencilInfo::API_DirectX12() const
	{
		D3D12_DEPTH_STENCIL_DESC d12Info{
			.DepthEnable = bDepthTest,
			.DepthWriteMask = bDepthWrite ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO,

			.StencilEnable = bStencilTest,
			.StencilReadMask = 0,
			.StencilWriteMask = 0,

			.FrontFace = {},
			.BackFace = {},
		};

		switch (method)
		{
		case DepthTestingMethod::Default:
		{
			d12Info.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			break;
		}
		case DepthTestingMethod::Inverse:
		{
			d12Info.DepthFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
			break;
		}
		}

		return d12Info;
	}

#endif
}
