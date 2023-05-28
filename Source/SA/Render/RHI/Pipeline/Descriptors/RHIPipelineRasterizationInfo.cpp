// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptors/RHIPipelineRasterizationInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkPipelineRasterizationStateCreateInfo PipelineRasterizationInfo::API_Vulkan() const
	{
		VkPipelineRasterizationStateCreateInfo vkInfo{};
		vkInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		vkInfo.pNext = nullptr;
		vkInfo.flags = 0u;
		vkInfo.depthClampEnable = bDepthTest ? VK_TRUE : VK_FALSE;
		vkInfo.rasterizerDiscardEnable = bConservative ? VK_FALSE : VK_TRUE;
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
}
