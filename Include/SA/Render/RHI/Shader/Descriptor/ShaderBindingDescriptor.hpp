// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_BINDING_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_BINDING_DESCRIPTOR_GUARD

#include <string>

#include "ShaderBindingType.hpp"

namespace SA::RND::RHI
{
	struct ShaderBindingDescriptor
	{
		/// Binding name (as written in shader).
		std::string name;

		/// Binding index in shader.
		uint32_t binding = 0u;

		/// Number of elements (array).
		uint32_t num = 1u;

		ShaderBindingType type = ShaderBindingType::UniformConstantBuffer;
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_BINDING_DESCRIPTOR_GUARD
