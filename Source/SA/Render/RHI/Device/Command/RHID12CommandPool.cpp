// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHID12CommandPool.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12CommandPool::Create(const Device* _device)
	{
		CommandPool::Create(_device);

		mHandle.Create(_device->API_DirectX12());
	}
	
	void D12CommandPool::Destroy(const Device* _device)
	{
		CommandPool::Destroy(_device);

		mHandle.Destroy();
	}


	const DX12::CommandAllocator& D12CommandPool::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
