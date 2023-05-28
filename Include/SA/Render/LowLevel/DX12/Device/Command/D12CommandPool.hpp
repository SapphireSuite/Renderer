// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#include "D12CommandList.hpp"

namespace SA::RND::DX12
{
	class Device;

	class CommandPool
	{
		MComPtr<ID3D12CommandAllocator> mHandle;

	public:
		void Create(const Device& _device, D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT);
		void Destroy();

		CommandList Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type);
		void Free(CommandList& _cmd);
	};
}

#endif // SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD
