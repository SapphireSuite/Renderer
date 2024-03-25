// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12RenderPass.hpp>

#include <Device/RHID12Device.hpp>
#include <Device/Command/RHID12CommandBuffer.hpp>

#include <Pass/RHID12FrameBuffer.hpp>

namespace SA::RND::RHI
{
	void D12RenderPass::Create(const Device* _device, const RenderPassInfo& _info)
	{
		(void)_device;
		mHandle.Create(DX12::API_GetRenderPassInfo(_info));
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
