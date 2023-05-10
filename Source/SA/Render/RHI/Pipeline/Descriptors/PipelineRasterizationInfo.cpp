// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptors/PipelineRasterizationInfo.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPipelineRasterizationStateCreateInfo API_GetPipelineRasterizationState(const RHI::PipelineRasterizationInfo& _pipRasterInfo)
		{
			VkPipelineRasterizationStateCreateInfo vkInfo{};
			vkInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			vkInfo.pNext = nullptr;
			vkInfo.flags = 0u;
			vkInfo.depthClampEnable = _pipRasterInfo.bDepthTest ? VK_TRUE : VK_FALSE;
			vkInfo.rasterizerDiscardEnable = _pipRasterInfo.bConservative ? VK_FALSE : VK_TRUE;
			vkInfo.polygonMode = API_GetPolygonMode(_pipRasterInfo.polygon);
			vkInfo.cullMode = API_GetCullingMode(_pipRasterInfo.cullingMode);
			vkInfo.frontFace = API_GetFrontFaceMode(_pipRasterInfo.frontFace);
			vkInfo.depthBiasEnable = VK_FALSE;
			vkInfo.depthBiasConstantFactor = 0.0f;
			vkInfo.depthBiasClamp = 0.0f;
			vkInfo.depthBiasSlopeFactor = 0.0f;
			vkInfo.lineWidth = 1.0f;

			return vkInfo;
		}
	}

#endif
}
