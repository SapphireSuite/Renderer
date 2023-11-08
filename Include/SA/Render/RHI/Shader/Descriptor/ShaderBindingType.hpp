// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD

#include <cstdint>

namespace SA
{
	enum class ShaderBindingType : uint8_t
	{
		/// Vk::Uniform / DX::Constant buffer binding
		UniformConstantBuffer = 1,

		StorageBuffer,

		InputAttachment,

		Texture,

		Sampler,
	};
}

#endif // SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD
