// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHID12Swapchain.hpp>

#include <RHIRenderInterface.hpp>
#include <Device/RHIDevice.hpp>
#include <Surface/RHIWindowSurface.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12Swapchain::Create(const RenderInterface* _renderIntf,
		const Device* _device,
		const WindowSurface* _winSurface,
		const SwapchainSettings& _settings)
	{
		mHandle.Create(_renderIntf->API_DirectX12(), _device->API_DirectX12(), _winSurface->API_DirectX12(), _settings.API_DirectX12());
	}

	void D12Swapchain::Destroy(const RenderInterface* _renderIntf, const Device* _device)
	{
		(void)_renderIntf;
		(void)_device;
		mHandle.Destroy();
	}

	Format D12Swapchain::GetFormat() const
	{
		return DX12::API_GetFormat(mHandle.GetFormat());
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
