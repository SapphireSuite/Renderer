// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIPipelineShaderStageInfo.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPipelineShaderStageCreateInfo API_GetPipelineShaderStageInfo(const RHI::PipelineShaderStageInfo& _info)
		{
			VkPipelineShaderStageCreateInfo vkInfo{};
			vkInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vkInfo.pNext = nullptr;
			vkInfo.flags = 0u;
			vkInfo.stage = API_GetShaderStage(_info.stage);
			vkInfo.module = *_info.shader->API_Vulkan();
			vkInfo.pName = _info.entry.c_str();
			vkInfo.pSpecializationInfo = nullptr;

			return vkInfo;
		}

		std::vector<VkPipelineShaderStageCreateInfo> API_GetPipelineShaderStagesInfo(const RHI::PipelineShaderStagesInfo& _info)
		{
			std::vector<VkPipelineShaderStageCreateInfo> vkInfos;
			vkInfos.reserve(_info.size());

			for(auto& _stageInfo : _info)
				vkInfos.emplace_back(API_GetPipelineShaderStageInfo(_stageInfo));

			return vkInfos;
		}
	}

#endif
}
