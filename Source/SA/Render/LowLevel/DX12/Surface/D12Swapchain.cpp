// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/D12Swapchain.hpp>

#include <D12Factory.hpp>
#include <Device/D12Device.hpp>
#include <Surface/D12WindowSurface.hpp>

namespace SA::RND::DX12
{
	void Swapchain::Create(const Factory& _factory, const Device& _device, const WindowSurface& _surface, const SwapchainSettings& _settings)
	{
		// Extents
		{
			RECT rect;
			GetWindowRect(_surface, &rect);

			mExtents.x = rect.right - rect.left;
			mExtents.y = rect.bottom - rect.top;
		}

		// Format
		{
			// TODO: Default format from surface?
			//const HDC hdc = GetDC(_surface);
			//const int pixelFormatIndex = GetPixelFormat(hdc);
			//PIXELFORMATDESCRIPTOR pfd;
			//DescribePixelFormat(hdc, pixelFormatIndex, sizeof(pfd), &pfd);

			mFormat = _settings.format;
		}

		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.BufferCount = _settings.frameNum != uint32_t(-1) ? _settings.frameNum : 3u;
		desc.Width = mExtents.x;
		desc.Height = mExtents.y;
		desc.Format = _settings.format;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.SampleDesc.Count = 1;

		// Queue to force flush.
		ID3D12CommandQueue* queue = nullptr;

		if(_device.queueMgr.present.GetQueueNum() > 0)
			queue = _device.queueMgr.present[0];
		else if(_device.queueMgr.graphics.GetQueueNum() > 0)
			queue = _device.queueMgr.graphics[0];
		//

		MComPtr<IDXGISwapChain1> swapChain1;
		SA_DX12_API(_factory->CreateSwapChainForHwnd(queue, _surface, &desc, nullptr, nullptr, &swapChain1));
		SA_DX12_API(swapChain1.As(&mHandle));
	}
	
	void Swapchain::Destroy()
	{
		if (mHandle)
		{
			SA_LOG_RAII(L"Swapchain destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

			mHandle.Reset();
		}
	}

	DXGI_FORMAT Swapchain::GetFormat() const noexcept
	{
		return mFormat;
	}
}
