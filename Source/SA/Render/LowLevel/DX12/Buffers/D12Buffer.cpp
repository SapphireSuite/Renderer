// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/D12Buffer.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void Buffer::Create(const Device& _device,
		uint32_t _size,
		D3D12_RESOURCE_STATES _usage,
		D3D12_HEAP_TYPE _memory,
		const void* _src)
	{
#if SA_DEBUG
		mHeapType = _memory;
#endif

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

	void Buffer::CopyData(const Device& _device, const void* _src, uint64_t _size, uint64_t _offset)
	{
		SA_ASSERT((Nullptr, _src), SA.Render.Vulkan);
#if SA_DEBUG
		SA_ASSERT((Default, (mHeapType & D3D12_HEAP_TYPE_UPLOAD)), SA.Render.DX12,
			L"Buffer must have `D3D12_HEAP_TYPE_UPLOAD` memory type to copy data from CPU to GPU");
#endif

		void* GPUData = nullptr;
		D3D12_RANGE mapRange{ _offset , _offset + _size };
		SA_DX12_API(mHandle->Map(0, &mapRange, &GPUData));

		std::memcpy(GPUData, _src, _size);

		SA_DX12_API(mHandle->Unmap(0, nullptr));
	}
}
