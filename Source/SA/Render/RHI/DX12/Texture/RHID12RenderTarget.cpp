// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHID12RenderTarget.hpp>

#include <Device/RHID12Device.hpp>

namespace SA::RND::RHI
{
	void D12RenderTarget::Create(const Device* _device, const RenderTargetDescriptor& _desc)
	{
		mHandle.Create(_device->API_DirectX12(), _desc.API_DirectX12());
	}

	void D12RenderTarget::CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex)
	{
		mHandle.CreateFromImage(_swapchain->API_DirectX12(), _imageIndex);
	}

	void D12RenderTarget::Destroy(const Device* _device)
	{
		mHandle.Destroy();
	}
}
