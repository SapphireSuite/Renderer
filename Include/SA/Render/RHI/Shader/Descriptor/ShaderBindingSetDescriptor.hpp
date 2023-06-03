// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include "ShaderBindingDescriptor.hpp"

namespace SA::RND::RHI
{
	struct ShaderBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<ShaderBindingDescriptor> bindings;
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_BINDING_SET_DESCRIPTOR_GUARD
