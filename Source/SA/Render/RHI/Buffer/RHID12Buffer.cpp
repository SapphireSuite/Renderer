// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffer/RHID12Buffer.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12Buffer::Create(const Device* _device, uint32_t _size, BufferUsage _usage, const void* _src)
	{
		mHandle.Create(_device->API_DirectX12(),
			_size,
			DX12::API_GetBufferUsage(_usage),
			DX12::API_GetBufferMemoryHeapType(_usage),
			_src
		);
	}

	void D12Buffer::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
