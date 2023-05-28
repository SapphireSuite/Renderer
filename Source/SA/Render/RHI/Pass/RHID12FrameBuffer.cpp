// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12FrameBuffer.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12FrameBuffer::Create(const Device* _device, const Pass* _pass)
	{
		// TODO: ADD Swapchain image handle.
		mHandle.Create(_device->API_DirectX12(), _pass->GetInfo().API_DirectX12());
	}
	
	void D12FrameBuffer::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}

	
	const const DX12::FrameBuffer& D12FrameBuffer::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL