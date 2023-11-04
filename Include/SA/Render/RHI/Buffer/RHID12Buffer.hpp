// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD

#include "RHIBuffer.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Buffers/D12Buffer.hpp>

namespace SA::RND::RHI
{
	class D12Buffer : public Buffer
	{
		DX12::Buffer mHandle;

	public:
		void Create(const Device* _device, uint32_t _size, BufferUsage _usage, const void* _src) override final;
		void Destroy(const Device* _device) override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL


#endif // SAPPHIRE_RENDER_RHI_DX12_BUFFER_GUARD
