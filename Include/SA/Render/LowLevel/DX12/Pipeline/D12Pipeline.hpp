// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_PIPELINE_GUARD
#define SAPPHIRE_RENDER_DX12_PIPELINE_GUARD

#include <SA/Render/LowLevel/DX12/Pipeline/Info/D12GraphicsPipelineInfo.hpp>

namespace SA::RND::DX12
{
	class Device;

	using DXPipelineT = MComPtr<ID3D12PipelineState>;

	class Pipeline
	{
		DXPipelineT mHandle = nullptr;
	
	public:
		void Create(const Device& _device, const GraphicsPipelineInfo& _info);
		void Create(const Device& _device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC& _desc);
		void Destroy();

		DXPipelineT operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_PIPELINE_GUARD
