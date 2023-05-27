// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD

#include <SA/Render/LowLevel/Common/Surface/SwapchainBase.hpp>

#include <SA/Render/LowLevel/DX12/Surface/D12SwapchainSettings.hpp>

namespace SA::RND::DX12
{
	class Factory;
	class Device;
	class WindowSurface;

	using DXSwapchainT = Microsoft::WRL::ComPtr<IDXGISwapChain3>;

	class Swapchain : public SwapchainBase
	{
//{ DXSwapchain

		DXSwapchainT mHandle = nullptr;

		void CreateDXSwapchain(const Factory& _factory,
			const Device& _device,
			const WindowSurface& _surface,
			const SwapchainSettings& _settings);
		void DestroyDXSwapchain();
//}

//{ Sync

		HANDLE mFenceEvent;
		MComPtr<ID3D12Fence> mFence;

		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation();

//}

//{ Frame

		struct Frame
		{
			/// Backbuffer image.
			MComPtr<ID3D12Resource> image = nullptr;

			uint64_t fenceValue = 0;
		};

		std::vector<Frame> mFrames;
		
		uint32_t mFrameIndex = 0u;
//}

		DXGI_FORMAT mFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	public:
		void Create(const Factory& _factory, const Device& _device, const WindowSurface& _surface, const SwapchainSettings& _settings);
		void Destroy();

		/// Get number of image (frame-buffering num).
		uint32_t GetImageNum() const noexcept;

		/// Get Swapchain backbuffer image handle at fame index.
		MComPtr<ID3D12Resource> GetBackBufferHandle(uint32_t _index) const;

		DXGI_FORMAT GetFormat() const noexcept;

		uint32_t Begin(const Device& _device);
		void End();
	};
}

#endif // SAPPHIRE_RENDER_DX12_SWAPCHAIN_GUARD
