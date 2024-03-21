// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_DESCRIPTOR_GUARD

#include <SA/Render/RHI/Common/Shader/Descriptor/RHIShaderStage.hpp>
#include <SA/Render/RHI/Common/Shader/Descriptor/ShaderBindingDescriptor.hpp>

namespace SA::RND::RHI
{
	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		/// Shader stage flags.
		uint8_t stageFlags = 0;
	};
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_BINDING_DESCRIPTOR_GUARD
