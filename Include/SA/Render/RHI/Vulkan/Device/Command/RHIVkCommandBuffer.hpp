// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD

#include <SA/Render/RHI/Common/Device/Command/RHICommandBuffer.hpp>

#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandBuffer.hpp>

namespace SA::RND::RHI
{
	class VkCommandPool;

	class VkCommandBuffer : public CommandBuffer
	{
		friend VkCommandPool;

		VK::CommandBuffer mHandle;

	public:
		void Begin() override final;
		void End() override final;

		void Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance) override final;

		VK::CommandBuffer& API_Vulkan() override final;
		const VK::CommandBuffer& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD
