// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_PIPELINE_GUARD
#define SAPPHIRE_RENDER_DX12_PIPELINE_GUARD

#include <SA/Render/LowLevel/DX12/Pipeline/D12RootSignature.hpp>
#include <SA/Render/LowLevel/DX12/Pipeline/Info/D12GraphicsPipelineInfo.hpp>

namespace SA::RND::DX12
{
	class Device;
	class CommandList;

	using DXPipelineT = MComPtr<ID3D12PipelineState>;

	enum class PipelineType
	{
		Unknown = 0,

		Graphics,

		Compute,
	};

	class Pipeline
	{
		DXPipelineT mHandle = nullptr;
	
		DXRootSignatureT mRootSignatureRef;

		PipelineType mType = PipelineType::Unknown;

	public:
		void Create(const Device& _device, const GraphicsPipelineInfo& _info);
		void Create(const Device& _device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC& _desc);
		void Destroy();

		void Bind(const CommandList& _cmdList);

		DXPipelineT operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_PIPELINE_GUARD
