// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHID12Swapchain.hpp>

#include <RHIRenderInterface.hpp>
#include <Device/RHIDevice.hpp>
#include <Surface/RHIWindowSurface.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	void D12Swapchain::Create(const RenderInterface* _renderIntf,
		const Device* _device,
		const WindowSurface* _winSurface,
		const SwapchainSettings& _settings)
	{
		mDevice = &_device->API_DirectX12();

		mHandle.Create(_renderIntf->API_DirectX12(), *mDevice, _winSurface->API_DirectX12(), _settings.API_DirectX12());
	}

	void D12Swapchain::Destroy(const RenderInterface* _renderIntf, const Device* _device)
	{
		(void)_renderIntf;
		(void)_device;

		SA_ASSERT((Equals, mDevice, &_device->API_DirectX12()), SA.Render.RHI, L"Device ptr should match to ensure correct destroy.");

		mHandle.Destroy();
		mDevice = nullptr;
	}

	Format D12Swapchain::GetFormat() const
	{
		return DX12::API_GetFormat(mHandle.GetFormat());
	}

	uint32_t D12Swapchain::GetImageNum() const
	{
		return mHandle.GetImageNum();
	}

	const Vec2ui& D12Swapchain::GetExtents() const
	{
		return mHandle.GetExtents();
	}


	uint32_t D12Swapchain::Begin()
	{
		return mHandle.Begin();
	}
	
	void D12Swapchain::End(std::vector<CommandBuffer*> _cmds)
	{
		SA_ASSERT((Nullptr, mDevice), SA.Render.RHI);

		std::vector<DX12::CommandList> d12Cmds;
		d12Cmds.reserve(_cmds.size());

		for (auto cmd : _cmds)
			d12Cmds.emplace_back(cmd->API_DirectX12());

		mHandle.End(*mDevice, d12Cmds);
	}


//{ BackBuffer

	MComPtr<ID3D12Resource> D12Swapchain::BackBufferHandle::API_DirectX12() const
	{
		return handle;
	}

	std::shared_ptr<Swapchain::BackBufferHandle> D12Swapchain::GetBackBufferHandle(uint32_t _index)
	{
		auto backBufferHandle = std::make_shared<D12Swapchain::BackBufferHandle>();

		backBufferHandle->handle = mHandle.GetBackBufferHandle(_index);

		return backBufferHandle;
	}

//}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
