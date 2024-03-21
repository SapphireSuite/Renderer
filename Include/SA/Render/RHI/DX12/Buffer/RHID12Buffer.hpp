// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD

#include <SA/Render/RHI/Common/Buffer/RHIBuffer.hpp>

#include <SA/Render/LowLevel/DX12/Buffers/D12Buffer.hpp>

namespace SA::RND::RHI
{
	class D12Buffer : public Buffer
	{
		DX12::Buffer mHandle;

	public:
		void Create(const Device* _device, uint64_t _size, BufferUsage _usage, const void* _src) override final;
		void Destroy(const Device* _device) override final;

		void UploadData(const void* _src, uint64_t _size, uint64_t _offset = 0u) override final;
		void ReadbackData(void* _dst, uint64_t _size, uint64_t _offset = 0u) override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD
