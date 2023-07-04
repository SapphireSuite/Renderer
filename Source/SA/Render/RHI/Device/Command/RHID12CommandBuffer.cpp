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


	void D12CommandBuffer::Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance)
	{
		mHandle.Draw(_vertexNum, _instanceNum, _firstVertex, _firstInstance);
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
