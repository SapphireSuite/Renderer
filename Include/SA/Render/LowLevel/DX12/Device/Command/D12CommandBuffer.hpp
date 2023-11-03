// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_DX12_COMMAND_BUFFER_GUARD

#include "D12CommandList.hpp"
#include "D12CommandAllocator.hpp"

namespace SA::RND::DX12
{
	class CommandBuffer
	{
		CommandList mCmdList;
		CommandAllocator mAllocator;

	public:
		void Create(const Device& _device, D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT);
		void Destroy();

		void Begin();
		void End();

		void Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance);

		operator const CommandList&() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_COMMAND_BUFFER_GUARD