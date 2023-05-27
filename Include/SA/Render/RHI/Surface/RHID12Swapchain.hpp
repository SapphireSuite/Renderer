// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD

#include "RHISwapchain.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Surface/D12Swapchain.hpp>

namespace SA::RND::RHI
{
	class D12Swapchain : public Swapchain
	{
		DX12::Swapchain mHandle;

	public:
		void Create(const RenderInterface* _renderIntf,
			const Device* _device,
			const WindowSurface* _winSurface,
			const SwapchainSettings& _settings) override final;
		void Destroy(const RenderInterface* _renderIntf, const Device* _device) override final;
		
		Format GetFormat() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD
