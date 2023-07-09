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

	public:
		void Create(const Device& _device, uint32_t _size, D3D12_RESOURCE_STATES _usage, D3D12_HEAP_TYPE _memory);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_DX12_BUFFER_GUARD
