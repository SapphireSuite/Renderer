// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffer/RHID12Buffer.hpp>

#include <Device/RHID12Device.hpp>

namespace SA::RND::RHI
{
	void D12Buffer::Create(const Device* _device, uint64_t _size, BufferUsage _usage, const void* _src)
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


	void D12Buffer::UploadData(const void* _src, uint64_t _size, uint64_t _offset)
	{
		mHandle.UploadData(_src, _size, _offset);
	}

	void D12Buffer::ReadbackData(void* _dst, uint64_t _size, uint64_t _offset)
	{
		mHandle.ReadbackData(_dst, _size, _offset);
	}
}
