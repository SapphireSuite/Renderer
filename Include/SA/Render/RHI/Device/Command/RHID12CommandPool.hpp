// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD

#include "RHICommandPool.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandAllocator.hpp>

namespace SA::RND::RHI
{
	class D12CommandPool : public CommandPool
	{
		DX12::CommandAllocator mHandle;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

		const DX12::CommandAllocator& API_DirectX12() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD
