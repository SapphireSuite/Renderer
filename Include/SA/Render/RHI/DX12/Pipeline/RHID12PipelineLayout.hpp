// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_PIPELINE_LAYOUT_GUARD

#include <SA/Render/RHI/Common/Pipeline/RHIPipelineLayout.hpp>

#include <SA/Render/LowLevel/DX12/Pipeline/D12RootSignature.hpp>

namespace SA::RND::RHI
{
	class D12PipelineLayout : public PipelineLayout
	{
		DX12::RootSignature mHandle;

	public:
		void Create(const Device* _device, const PipelineLayoutDescriptor& _desc) override final;
		void Destroy(const Device* _device) override final;

		const DX12::RootSignature& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_PIPELINE_LAYOUT_GUARD
