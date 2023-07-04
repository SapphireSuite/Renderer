// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD

#include "RHIPipeline.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pipeline/D12Pipeline.hpp>

namespace SA::RND::RHI
{
	class D12Pipeline : public Pipeline
	{
		DX12::Pipeline mHandle;

	public:
		void Create(const Device* _device, const GraphicsPipelineInfo& _info) override final;
		void Destroy(const Device* _device) override final;

		void Bind(const CommandBuffer* _cmd) override final;

		const DX12::Pipeline& API_DirectX12() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD
