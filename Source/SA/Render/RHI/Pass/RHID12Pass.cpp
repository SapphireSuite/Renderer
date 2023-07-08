// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12Pass.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>
#include <Device/Command/RHID12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	void D12Pass::Create(const Device* _device, PassInfo _info)
	{
		mHandle.Create(_info.API_DirectX12());

		Pass::Create(_device, std::move(_info));
	}
	
	void D12Pass::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}

	void D12Pass::Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff)
	{
		mHandle.Begin(_cmd->API_DirectX12().GetCommandList(), _fBuff->API_DirectX12());
	}

	void D12Pass::NextSubpass(const CommandBuffer* _cmd)
	{
		mHandle.NextSubpass(_cmd->API_DirectX12().GetCommandList());
	}

	void D12Pass::End(const CommandBuffer* _cmd)
	{
		mHandle.End(_cmd->API_DirectX12().GetCommandList());
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
