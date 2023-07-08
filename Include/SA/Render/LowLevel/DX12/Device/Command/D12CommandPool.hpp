// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD

#include "D12CommandBuffer.hpp"

namespace SA::RND::DX12
{
	class CommandPool
	{
	public:
		void Create(const Device& _device);
		void Destroy();

		CommandBuffer Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT);
		std::vector<CommandBuffer> AllocateMultiple(const Device& _device, uint32_t _num, D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT);
	
		void Free(CommandBuffer& _cmd);
		void FreeMultiple(std::vector<CommandBuffer>& _cmds);
	};
}

#endif // SAPPHIRE_RENDER_DX12_COMMAND_POOL_GUARD
