// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineShaderStageInfo.hpp>

#include <SA/Render/RHI/Common/Shader/RHIShader.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Shader/D12Shader.hpp>

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


#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace Intl
	{
		D3D12_SHADER_BYTECODE API_MakeDX12ShaderByteCode(Shader* _shader)
		{
			auto& dxShader = _shader->API_DirectX12();

			return D3D12_SHADER_BYTECODE
			{
				.pShaderBytecode = dxShader->GetBufferPointer(),
				.BytecodeLength = dxShader->GetBufferSize(),
			};
		}
	}

	DX12::GraphicsPipelineShaderStages GraphicsPipelineShaderStageInfo::API_MakeDX12PipelineShaderStages() const
	{
		DX12::GraphicsPipelineShaderStages dxShaderStages;

		if (vs)
			dxShaderStages.vs = Intl::API_MakeDX12ShaderByteCode(vs);

		if (gs)
			dxShaderStages.gs = Intl::API_MakeDX12ShaderByteCode(gs);

		if (ps)
			dxShaderStages.ps = Intl::API_MakeDX12ShaderByteCode(ps);

		return dxShaderStages;
	}

#endif
}
