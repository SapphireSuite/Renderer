// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineInfo.hpp>

#include <Pass/RHIPass.hpp>
#include <Shader/RHIShader.hpp>
#include <Pipeline/RHIPipelineLayout.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pipeline/Info/VkGraphicsPipelineInfo.hpp>

#endif

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::GraphicsPipelineInfo GraphicsPipelineInfo::API_Vulkan() const
	{
		VK::GraphicsPipelineInfo vkInfo;

		vkInfo.shaderStages = shaders.API_MakeVkPipelineShaderStagesInfo();
		vkInfo.vertexInputState = shaders.vs->GetDescriptor().MakeVkVertexInputStateInfo();
		vkInfo.raster = raster.API_Vulkan();


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

		return vkInfo;
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
}