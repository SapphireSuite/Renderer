// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD

#include "ShaderBindingSetDescriptor.hpp"

namespace SA::RND::RHI
{
	struct ShaderDescriptor
	{
		std::vector<ShaderBindingSetDescriptor> sets;
	};
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_DESCRIPTOR_GUARD
