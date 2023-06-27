// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD

#include "RHICommandBuffer.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandList.hpp>

namespace SA::RND::RHI
{
	class D12CommandPool;

	class D12CommandBuffer : public CommandBuffer
	{
		friend D12CommandPool;

		DX12::CommandList mHandle;

	public:
		const DX12::CommandList& API_DirectX12() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD
