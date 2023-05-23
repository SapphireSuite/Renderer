// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD

#include <SA/Render/LowLevel/Common/Surface/Swapchain.hpp>

#include <SA/Render/LowLevel/DX12/Surface/D12SwapchainSettings.hpp>

namespace SA::RND::DX12
{
	class Factory;
	class Device;
	class WindowSurface;

	using DXSwapchainT = Microsoft::WRL::ComPtr<IDXGISwapChain3>;

	class Swapchain : public SA::RND::Swapchain
	{
		DXSwapchainT mHandle = nullptr;

	public:
		void Create(const Factory& _factory, const Device& _device, const WindowSurface& _surface, const SwapchainSettings& _settings);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD
