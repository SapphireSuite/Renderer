// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

#endif

namespace SA::RND::RHI
{
	class Shader
	{
	public:

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		virtual const VK::Shader& API_Vulkan() const;
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_GUARD
