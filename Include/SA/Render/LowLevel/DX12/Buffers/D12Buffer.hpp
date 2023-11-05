// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_BUFFER_GUARD
#define SAPPHIRE_RENDER_DX12_BUFFER_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class Device;

	class Buffer
	{
		MComPtr<ID3D12Resource> mHandle;

#if SA_DEBUG
		D3D12_HEAP_TYPE mHeapType;
#endif

	public:
		ID3D12Resource* Get() const;

		/**
		* Create a GPU memory buffer.
		*
		* @param[in] _src	Data to copy to the buffer. HeapType must be D3D12_HEAP_TYPE_UPLOAD.
		*/
		void Create(const Device& _device,
			uint64_t _size,
			D3D12_RESOURCE_STATES _usage,
			D3D12_HEAP_TYPE _memory,
			const void* _src = nullptr);
		void Destroy();

		/**
		* Copy data from the CPU to the GPU Buffer.
		* MemoryPropertyFlags must contain `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT`
		*/
		void CopyCPUToGPUData(const void* _src, uint64_t _size, uint64_t _offset = 0u);

		ID3D12Resource* operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_BUFFER_GUARD
