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

	class Pipeline
	{
	protected:
		DXPipelineT mHandle = nullptr;
	
		DXRootSignatureT mRootSignatureRef;

	public:
		virtual ~Pipeline() = default;

		void Destroy();

		virtual void Bind(const CommandList& _cmdList) = 0;

		DXPipelineT operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_PIPELINE_GUARD
