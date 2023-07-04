// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/D12Swapchain.hpp>

#include <D12Factory.hpp>
#include <Device/D12Device.hpp>
#include <Device/Command/D12CommandList.hpp>
#include <Surface/D12WindowSurface.hpp>

#include "../Misc/D12Format.hpp"

namespace SA::RND::DX12
{
//{ DXSwapchain

	void Swapchain::CreateDXSwapchain(const Factory& _factory,
		const Device& _device,
		const WindowSurface& _surface,
		const SwapchainSettings& _settings)
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

		const uint32_t frameNum = _settings.frameNum != uint32_t(-1) ? _settings.frameNum : 3u;

		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.BufferCount = frameNum;
		desc.Width = mExtents.x;
		desc.Height = mExtents.y;
		desc.Format = Intl::SRGBToUNORMFormat(_settings.format);
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.SampleDesc.Count = 1;

		// Queue to force flush.
		ID3D12CommandQueue* queue = nullptr;

		if(_device.queueMgr.graphics.GetQueueNum() > 0)
			queue = _device.queueMgr.graphics[0];
		//

		MComPtr<IDXGISwapChain1> swapChain1;
		SA_DX12_API(_factory->CreateSwapChainForHwnd(queue, _surface, &desc, nullptr, nullptr, &swapChain1));
		SA_DX12_API(swapChain1.As(&mHandle));

		// Frame
		mFrames.resize(frameNum);

		for (uint32_t i = 0; i < frameNum; ++i)
		{
			mHandle->GetBuffer(i, IID_PPV_ARGS(&mFrames[i].image));
			SetDebugName(mFrames[i].image.Get(), SA::StringFormat(L"Swapchain Image %1", i));
		}
		//

		SA_LOG(L"Swapchain created!", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}

	void Swapchain::DestroyDXSwapchain()
	{
		if (mHandle)
		{
			SA_LOG_RAII(L"Swapchain destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

			mHandle.Reset();
		}
	}
//}

//{ Sync

	void Swapchain::CreateSynchronisation(const Device& _device)
	{
		SA_DX12_API(_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));

		mFenceEvent = CreateEvent(nullptr, false, false, nullptr);
		SA_ASSERT((Nullptr, mFenceEvent), SA.Render.DX12, (L"Failed to create FenceEvent: %1", HRESULT_FROM_WIN32(GetLastError())));
	
		SA_LOG(L"Swapchain synchronisation created.", Info, SA.Render.DX12);
	}
	
	void Swapchain::DestroySynchronisation()
	{
		mFence.Reset();

		CloseHandle(mFenceEvent);

		SA_LOG(L"Swapchain synchronisation destroyed.", Info, SA.Render.DX12);
	}

//}

	void Swapchain::Create(const Factory& _factory, const Device& _device, const WindowSurface& _surface, const SwapchainSettings& _settings)
	{
		CreateDXSwapchain(_factory, _device, _surface, _settings);
		CreateSynchronisation(_device);
	}
	
	void Swapchain::Destroy()
	{
		DestroySynchronisation();
		DestroyDXSwapchain();
	}

	uint32_t Swapchain::GetImageNum() const noexcept
	{
		return static_cast<uint32_t>(mFrames.size());
	}

	MComPtr<ID3D12Resource> Swapchain::GetBackBufferHandle(uint32_t _index) const
	{
		SA_ASSERT((OutOfArrayRange, _index, mFrames), SA.Render.DX12);

		return mFrames[_index].image;
	}


	DXGI_FORMAT Swapchain::GetFormat() const noexcept
	{
		return mFormat;
	}


	uint32_t Swapchain::Begin()
	{
		const UINT64 prevFenceValue = mFrames[mFrameIndex].fenceValue;

		mFrameIndex = mHandle->GetCurrentBackBufferIndex();

		// If the next frame is not ready to be rendered yet, wait until it is ready.
		if (mFence->GetCompletedValue() < mFrames[mFrameIndex].fenceValue)
		{
			SA_DX12_API(mFence->SetEventOnCompletion(mFrames[mFrameIndex].fenceValue, mFenceEvent));
			WaitForSingleObjectEx(mFenceEvent, INFINITE, FALSE);
		}

		// Set the fence value for the next frame.
		mFrames[mFrameIndex].fenceValue = prevFenceValue + 1;

		return mFrameIndex;
	}

	void Swapchain::End(const Device& _device, const std::vector<CommandList>& _cmds)
	{
		ID3D12CommandQueue* graphics = _device.queueMgr.graphics[0];
		//ID3D12CommandQueue* present = _device.queueMgr.present.GetQueueNum() > 0 ? _device.queueMgr.present[0] : graphics;

		End(graphics/*, present*/, _cmds);
	}

	void Swapchain::End(ID3D12CommandQueue* _graphicsQueue/*, ID3D12CommandQueue* presentQueue*/, const std::vector<CommandList>& _cmds)
	{
		// Execute commands
		{
			std::vector<ID3D12CommandList*> d12Cmds;
			d12Cmds.reserve(_cmds.size());

			for (auto& cmd : _cmds)
				d12Cmds.emplace_back(cmd.Get());

			_graphicsQueue->ExecuteCommandLists(
				static_cast<uint32_t>(d12Cmds.size()),
				d12Cmds.data()
			);
		}

		// Present already handle Present queue.
		SA_DX12_API(mHandle->Present(1, 0));

		// Schedule a Signal command in the queue.
		const UINT64 currFenceValue = mFrames[mFrameIndex].fenceValue;
		SA_DX12_API(_graphicsQueue->Signal(mFence.Get(), currFenceValue));
		//SA_DX12_API(presentQueue->Signal(mFence.Get(), currFenceValue));
	}
}
