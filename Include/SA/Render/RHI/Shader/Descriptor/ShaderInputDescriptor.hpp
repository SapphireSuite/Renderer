// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD

#include <string>
#include <cstdint>

#include <SA/Render/RHI/Misc/RHIFormat.hpp>

namespace SA::RND::RHI
{
	struct ShaderInputDescriptor
	{
		std::string semantic;

		uint32_t location = 0u;

		uint32_t size = 0u;

		Format format = Format::Unknown;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_INPUT_DESCRIPTOR_GUARD
