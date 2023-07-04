// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_GRAPHICS_PIPELINE_GUARD
#define SAPPHIRE_RENDER_DX12_GRAPHICS_PIPELINE_GUARD

#include "D12Pipeline.hpp"

namespace SA::RND::DX12
{
	class GraphicsPipeline : public Pipeline
	{
		GraphicsPipelineViewInfo mViews;

	public:
		void Create(const Device& _device, const GraphicsPipelineInfo& _info);
		void Create(const Device& _device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC& _desc);

		void Bind(const CommandList& _cmdList) override final;
	};
}

#endif // SAPPHIRE_RENDER_DX12_GRAPHICS_PIPELINE_GUARD
