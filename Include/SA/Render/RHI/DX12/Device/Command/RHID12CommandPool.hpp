// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD

#include <SA/Render/RHI/Common/Device/Command/RHICommandPool.hpp>

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandPool.hpp>

namespace SA::RND::RHI
{
	class D12CommandPool : public CommandPool
	{
		DX12::CommandPool mHandle;

		const DX12::Device* mD12Device = nullptr;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

	//{ Allocation
		
		CommandBuffer* Allocate() override final;
		std::vector<CommandBuffer*> Allocate(uint32_t _num) override final;

		void Free(CommandBuffer* _cmd) override final;
		void Free(std::vector<CommandBuffer*>& _cmds) override final;

	//}

		const DX12::CommandPool& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_COMMAND_POOL_GUARD
