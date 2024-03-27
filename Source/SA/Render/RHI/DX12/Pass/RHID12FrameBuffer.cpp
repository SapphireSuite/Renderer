// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12FrameBuffer.hpp>

#include <Device/RHID12Device.hpp>
#include <Pass/RHID12RenderPass.hpp>

namespace SA::RND::RHI
{
	void D12FrameBuffer::Create(const Device* _device, const RenderPass* _pass, const RenderPassInfo& _info)
	{
		(void)_pass;
		mHandle.Create(_device->API_DirectX12(), DX12::API_GetRenderPassInfo(_info));
	}

	void D12FrameBuffer::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}
}
