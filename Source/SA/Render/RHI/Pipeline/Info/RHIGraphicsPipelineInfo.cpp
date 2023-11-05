// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineInfo.hpp>

#include <Pass/RHIPass.hpp>
#include <Shader/RHIShader.hpp>
#include <Pipeline/RHIRenderViews.hpp>
#include <Pipeline/RHIPipelineLayout.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pipeline/Info/VkGraphicsPipelineInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pipeline/Info/D12GraphicsPipelineInfo.hpp>

#endif

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::GraphicsPipelineInfo GraphicsPipelineInfo::API_Vulkan() const
	{
		VK::GraphicsPipelineInfo vkInfo;

		vkInfo.shaderStages = shaders.API_MakeVkPipelineShaderStagesInfo();
		vkInfo.vertexInputState = shaders.vs->GetDescriptor().MakeVkVertexInputStateInfoSingleVertexBuffer();
		vkInfo.raster = raster.API_Vulkan();
		vkInfo.depthStencil = depthStencil.API_Vulkan();

		auto& passInfo = pass->GetInfo();

		const VkSampleCountFlagBits vkSampling = VK::API_GetSampleCount(passInfo.subpasses[subpassIndex].sampling);

		vkInfo.multisampling = VkPipelineMultisampleStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.rasterizationSamples = vkSampling,
			.sampleShadingEnable = vkSampling != VK_SAMPLE_COUNT_1_BIT,
			.minSampleShading = 0.2f,
			.pSampleMask = nullptr,
			.alphaToCoverageEnable = VK_FALSE,
			.alphaToOneEnable = VK_FALSE,
		};


		vkInfo.layout = &layout->API_Vulkan();

		vkInfo.renderPass = &pass->API_Vulkan();
		vkInfo.subpassIndex = subpassIndex;

		vkInfo.views = &views->API_Vulkan();

		return vkInfo;
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	DX12::GraphicsPipelineInfo GraphicsPipelineInfo::API_DirectX12() const
	{
		DX12::GraphicsPipelineInfo dxDesc;

		dxDesc.rootSign = &layout->API_DirectX12();

		dxDesc.shaderStages = shaders.API_MakeDX12PipelineShaderStages();
		dxDesc.raster = raster.API_DirectX12();
		dxDesc.depthStencil = depthStencil.API_DirectX12();

		dxDesc.vertexInputElements = shaders.vs->GetDescriptor().MakeDX12VertexInputElementDescsSingleVertexBuffer();

		const auto& passInfo = pass->GetInfo();
		const auto& subpassInfo = passInfo.subpasses[subpassIndex];

		for (uint32_t i = 0, rtvIndex = 0; i < subpassInfo.attachments.size(); ++i)
		{
			if (subpassInfo.attachments[i].type == AttachmentType::Color)
				dxDesc.rtvFormats[rtvIndex++] = DX12::API_GetFormat(subpassInfo.attachments[i].format);
			else if(subpassInfo.attachments[i].type == AttachmentType::Depth)
				dxDesc.dsvFormat = DX12::API_GetFormat(subpassInfo.attachments[i].format);
		}

		dxDesc.sampling = DX12::API_GetSampleCount(subpassInfo.sampling);

		return dxDesc;
	}
#endif
}