// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD

#include <SA/Render/RHI/Common/Device/Command/RHICommandBuffer.hpp>

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	class D12CommandPool;

	class D12CommandBuffer : public CommandBuffer
	{
		friend D12CommandPool;

		DX12::CommandBuffer mHandle;

	public:
		void Begin() override final;
		void End() override final;

		void Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance) override final;

		DX12::CommandBuffer& API_DirectX12() override final;
		const DX12::CommandBuffer& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_COMMAND_BUFFER_GUARD
