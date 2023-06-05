// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_STAGE_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_STAGE_GUARD

#include <cstdint>
#include <string>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum ShaderStage : uint8_t
		{
			Unknown = 0,

			Vertex = 1 << 0,

			Pixel = 1 << 1,
			Fragment = Pixel,

			Geometry = 1 << 2,

			Compute = 1 << 3,
		};
	
		ShaderStage GetShaderStageFromTarget(const std::string& _target);

	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkShaderStageFlagBits API_GetShaderStage(RHI::ShaderStage _type) noexcept;

		VkShaderStageFlags API_GetShaderStageFlags(RHI::ShaderStage _flags) noexcept;
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_STAGE_GUARD
