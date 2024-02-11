// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD

#include "RHIFrameBuffer.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pass/D12FrameBuffer.hpp>

namespace SA::RND::RHI
{
	class D12FrameBuffer : public FrameBuffer
	{
		DX12::FrameBuffer mHandle;

	public:
		void Create(const Device* _device, const RenderPass* _pass,
			std::shared_ptr<Swapchain::BackBufferHandle> _img) override final;
		void Destroy(const Device* _device) override final;

		DX12::FrameBuffer& API_DirectX12() override final;
		const DX12::FrameBuffer& API_DirectX12() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_DX12_FRAMEBUFFER_GUARD
