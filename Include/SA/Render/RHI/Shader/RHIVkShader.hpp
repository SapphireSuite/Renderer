// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include "RHIShader.hpp"

#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

namespace SA::RND::RHI
{
	class VkShader : public Shader
	{
		VK::Shader mHandle;
		
	public:
		const VK::Shader& API_Vulkan() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD
