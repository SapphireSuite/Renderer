// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_RENDER_PASS_GUARD

#include <SA/Render/RHI/Common/Pass/RHIRenderPass.hpp>

#include <SA/Render/LowLevel/DX12/Pass/D12RenderPass.hpp>

namespace SA::RND::RHI
{
	class D12RenderPass : public RenderPass
	{
		DX12::RenderPass mHandle;

	public:
		void Create(const Device* _device, RenderPassInfo _info) override final;
		void Destroy(const Device* _device) override final;

		void Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff) override final;
		void NextSubpass(const CommandBuffer* _cmd) override final;
		void End(const CommandBuffer* _cmd) override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_RENDER_PASS_GUARD
