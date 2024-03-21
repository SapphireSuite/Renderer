// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD

#include <string>
#include <cstdint>

#include <SA/Render/RHI/Common/Misc/RHIFormat.hpp>

namespace SA::RND::RHI
{
	struct ShaderInputDescriptor
	{
		std::string semantic;

		union
		{
#if SA_RENDER_LOWLEVEL_DX12_IMPL
			/// HLSL
			uint32_t reg;
#endif

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENGL_IMPL
			/// SPIRV
			uint32_t location = 0u;
#endif
		};

		uint32_t size = 0u;

		Format format = Format::Unknown;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD
