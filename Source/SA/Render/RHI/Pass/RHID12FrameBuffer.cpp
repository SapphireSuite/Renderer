// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12FrameBuffer.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12FrameBuffer::Create(const Device* _device, const RenderPass* _pass,
		std::shared_ptr<Swapchain::BackBufferHandle> _img)
	{
		mHandle.Create(_device->API_DirectX12(), _pass->GetInfo().API_DirectX12(),
			_img ? _img->API_DirectX12() : nullptr);
	}
	
	void D12FrameBuffer::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}

	
	DX12::FrameBuffer& D12FrameBuffer::API_DirectX12()
	{
		return mHandle;
	}

	const DX12::FrameBuffer& D12FrameBuffer::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL