// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHID12CommandBuffer.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12CommandBuffer::Begin()
	{
		mHandle.Begin();
	}

	void D12CommandBuffer::End()
	{
		mHandle.End();
	}


	DX12::CommandBuffer& D12CommandBuffer::API_DirectX12()
	{
		return mHandle;
	}

	const DX12::CommandBuffer& D12CommandBuffer::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
