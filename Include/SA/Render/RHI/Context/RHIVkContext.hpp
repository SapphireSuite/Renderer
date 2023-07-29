// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD

#include "RHIContext.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	class VkContext : public Context
	{
	protected:
		Pass* InstantiatePassClass() override final;
		FrameBuffer* InstantiateFrameBufferClass() override final;
		Shader* InstantiateShaderClass() override final;
		RenderViews* InstantiateRenderViewsClass() override final;
		PipelineLayout* InstantiatePipelineLayoutClass() override final;
		Pipeline* InstantiatePipelineClass() override final;
		CommandPool* InstantiateCommandPoolClass() override final;
		Buffer* InstantiateBufferClass() override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
