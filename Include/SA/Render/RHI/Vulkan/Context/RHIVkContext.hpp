// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD

#include <SA/Render/RHI/Common/Context/RHIContext.hpp>

namespace SA::RND::RHI
{
	class VkContext : public Context
	{
	protected:
		RenderPass* InstantiateRenderPassClass() override final;
		FrameBuffer* InstantiateFrameBufferClass() override final;
		Shader* InstantiateShaderClass() override final;
		RenderViews* InstantiateRenderViewsClass() override final;
		PipelineLayout* InstantiatePipelineLayoutClass() override final;
		Pipeline* InstantiatePipelineClass() override final;
		CommandPool* InstantiateCommandPoolClass() override final;
		Buffer* InstantiateBufferClass() override final;
		ResourceInitializer* InstantiateResourceInitializerClass() override final;
		StaticMesh* InstantiateStaticMeshClass() override final;
		InputTexture* InstantiateInputTextureClass() override final;
		RenderTarget* InstantiateRenderTargetClass() override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
