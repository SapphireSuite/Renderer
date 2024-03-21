// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12RenderPass.hpp>

#include <Device/RHID12Device.hpp>
#include <Device/Command/RHID12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	void D12RenderPass::Create(const Device* _device, RenderPassInfo _info)
	{
		//mHandle.Create(_info.API_DirectX12());

		RenderPass::Create(_device, std::move(_info));
	}
	
	void D12RenderPass::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}

	void D12RenderPass::Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff)
	{
		mHandle.Begin(_cmd->API_DirectX12(), _fBuff->API_DirectX12());
	}

	void D12RenderPass::NextSubpass(const CommandBuffer* _cmd)
	{
		mHandle.NextSubpass(_cmd->API_DirectX12());
	}

	void D12RenderPass::End(const CommandBuffer* _cmd)
	{
		mHandle.End(_cmd->API_DirectX12());
	}
}
