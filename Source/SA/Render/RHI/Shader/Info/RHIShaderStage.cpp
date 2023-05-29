// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/Info/RHIShaderStage.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkShaderStageFlagBits API_GetShaderStage(RHI::ShaderStage _type) noexcept
		{
			switch (_type)
			{
			case RHI::ShaderStage::Vertex:
				return VK_SHADER_STAGE_VERTEX_BIT;
			case RHI::ShaderStage::Fragment:
				return VK_SHADER_STAGE_FRAGMENT_BIT;
			case RHI::ShaderStage::Geometry:
				return VK_SHADER_STAGE_GEOMETRY_BIT;
			case RHI::ShaderStage::Compute:
				return VK_SHADER_STAGE_COMPUTE_BIT;
			case RHI::ShaderStage::Unknown:
			default:
				SA_LOG(L"ShaderStage [%1] not supported yet!", Error, SA.Render.RHI.Vulkan);
				return VkShaderStageFlagBits(0);
			}
		}

		VkShaderStageFlags API_GetShaderStageFlags(RHI::ShaderStage _flags) noexcept
		{
			VkShaderStageFlags result = 0;

			if (_flags & RHI::ShaderStage::Vertex)
				result |= VK_SHADER_STAGE_VERTEX_BIT;

			if (_flags & RHI::ShaderStage::Fragment)
				result |= VK_SHADER_STAGE_FRAGMENT_BIT;

			if (_flags & RHI::ShaderStage::Geometry)
				result |= VK_SHADER_STAGE_GEOMETRY_BIT;

			if (_flags & RHI::ShaderStage::Compute)
				result |= VK_SHADER_STAGE_COMPUTE_BIT;

			return result;
		}
	}

#endif
}
