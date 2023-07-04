// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineRasterizationInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkPipelineRasterizationStateCreateInfo GraphicsPipelineRasterizationInfo::API_Vulkan() const
	{
		VkPipelineRasterizationStateCreateInfo vkInfo{};
		vkInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		vkInfo.pNext = nullptr;
		vkInfo.flags = 0u;
		vkInfo.depthClampEnable = bDepthTest ? VK_TRUE : VK_FALSE;
		vkInfo.rasterizerDiscardEnable = VK_FALSE;
		vkInfo.polygonMode = VK::API_GetPolygonMode(polygon);
		vkInfo.cullMode = VK::API_GetCullingMode(cullingMode);
		vkInfo.frontFace = VK::API_GetFrontFaceMode(frontFace);
		vkInfo.depthBiasEnable = VK_FALSE;
		vkInfo.depthBiasConstantFactor = 0.0f;
		vkInfo.depthBiasClamp = 0.0f;
		vkInfo.depthBiasSlopeFactor = 0.0f;
		vkInfo.lineWidth = 1.0f;

		return vkInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	D3D12_RASTERIZER_DESC GraphicsPipelineRasterizationInfo::API_DirectX12() const
	{
		D3D12_RASTERIZER_DESC d12Desc{};
		d12Desc.FillMode = D3D12_FILL_MODE_SOLID;
		d12Desc.CullMode = DX12::API_GetCullingMode(cullingMode);
		d12Desc.FrontCounterClockwise = DX12::API_GetFrontFaceMode(frontFace);
		d12Desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		d12Desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		d12Desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		d12Desc.DepthClipEnable = bDepthTest;
		d12Desc.MultisampleEnable = false;
		d12Desc.AntialiasedLineEnable = false;
		d12Desc.ForcedSampleCount = 0;
		d12Desc.ConservativeRaster = bConservative ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	
		return d12Desc;
	}

#endif
}
