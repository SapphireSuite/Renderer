// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD

#include <SA/Render/RHI/Common/Pass/RHIFrameBuffer.hpp>

#include <SA/Render/LowLevel/DX12/Pass/D12FrameBuffer.hpp>

namespace SA::RND::RHI
{
	class D12FrameBuffer : public FrameBuffer
	{
		DX12::FrameBuffer mHandle;

	public:
		void Create(const Device* _device, const RenderPass* _pass) override final;
		void Destroy(const Device* _device) override final;

		DX12::FrameBuffer& API_DirectX12() override final;
		const DX12::FrameBuffer& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD
