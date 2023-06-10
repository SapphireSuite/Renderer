// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_D12_CONTEXT_GUARD

#include "RHIContext.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	class D12Context : public Context
	{
	protected:
		Pass* InstantiatePassClass() override final;
		FrameBuffer* InstantiateFrameBufferClass() override final;
		Shader* InstantiateShaderClass() override final;
		PipelineLayout* InstantiatePipelineLayoutClass() override final;
		Pipeline* InstantiatePipelineClass() override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
