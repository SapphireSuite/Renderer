// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineShaderStageInfo.hpp>

#include <SA/Render/RHI/Shader/RHIShader.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

#endif

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace Intl
	{
		VkPipelineShaderStageCreateInfo API_MakeVkPipelineShaderStageInfo(const RHI::Shader* _shader)
		{
			const RHI::ShaderDescriptor& desc = _shader->GetDescriptor();

			VkPipelineShaderStageCreateInfo vkInfo
			{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.stage = VK::API_GetShaderStage(desc.stage),
				.module = _shader->API_Vulkan(),
				.pName = desc.entrypoint.c_str(),
				.pSpecializationInfo = nullptr,
			};

			return vkInfo;
		}
	}

	std::vector<VkPipelineShaderStageCreateInfo> GraphicsPipelineShaderStageInfo::API_MakeVkPipelineShaderStagesInfo() const
	{
		std::vector<VkPipelineShaderStageCreateInfo> vkInfos;
		vkInfos.reserve(3);

		if (vs)
			vkInfos.emplace_back(Intl::API_MakeVkPipelineShaderStageInfo(vs));

		if (gs)
			vkInfos.emplace_back(Intl::API_MakeVkPipelineShaderStageInfo(gs));

		if (ps)
			vkInfos.emplace_back(Intl::API_MakeVkPipelineShaderStageInfo(ps));

		return vkInfos;
	}

#endif
}
