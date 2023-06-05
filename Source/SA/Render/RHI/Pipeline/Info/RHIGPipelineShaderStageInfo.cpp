// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGPipelineShaderStageInfo.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

#endif

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPipelineShaderStageCreateInfo API_GetPipelineShaderStageInfo(const RHI::Shader* _shader)
		{
			const RHI::ShaderDescriptor& desc = _shader->GetDescriptor();

			VkPipelineShaderStageCreateInfo vkInfo{};
			vkInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vkInfo.pNext = nullptr;
			vkInfo.flags = 0u;
			vkInfo.stage = API_GetShaderStage(desc.stage);
			vkInfo.module = _shader->API_Vulkan();
			vkInfo.pName = desc.entrypoint.c_str();
			vkInfo.pSpecializationInfo = nullptr;

			return vkInfo;
		}

		std::vector<VkPipelineShaderStageCreateInfo> API_GetPipelineShaderStagesInfo(const RHI::GPipelineShaderStageInfo& _info)
		{
			std::vector<VkPipelineShaderStageCreateInfo> vkInfos;
			vkInfos.reserve(3);

			if (_info.vs)
				vkInfos.emplace_back(API_GetPipelineShaderStageInfo(_info.vs));

			if (_info.gs)
				vkInfos.emplace_back(API_GetPipelineShaderStageInfo(_info.gs));

			if (_info.ps)
				vkInfos.emplace_back(API_GetPipelineShaderStageInfo(_info.ps));

			return vkInfos;
		}
	}

#endif
}
