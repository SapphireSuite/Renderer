// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/D12Buffer.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void Buffer::Create(const Device& _device, uint32_t _size, D3D12_RESOURCE_STATES _usage, D3D12_HEAP_TYPE _memory)
	{
		D3D12_HEAP_PROPERTIES heap{
			.Type = _memory,
		};

		D3D12_RESOURCE_DESC desc{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0,
			.Width = _size,
			.Height = 1,
			.DepthOrArraySize = 1,
			.MipLevels = 1,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc { .Count = 1, .Quality = 0 },
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
		};

		SA_DX12_API(_device->CreateCommittedResource(&heap,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			_usage,
			nullptr,
			IID_PPV_ARGS(&mHandle)
		));

		SA_LOG("Buffer created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}

	void Buffer::Destroy()
	{
		SA_LOG_RAII("Buffer destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

		mHandle.Reset();
	}
}
