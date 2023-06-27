// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD

#include "RHICommandBuffer.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandBuffer.hpp>

namespace SA::RND::RHI
{
	class VkCommandPool;

	class VkCommandBuffer : public CommandBuffer
	{
		friend VkCommandPool;

		VK::CommandBuffer mHandle;

	public:
		VK::CommandBuffer& API_Vulkan() override final;
		const VK::CommandBuffer& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_COMMAND_BUFFER_GUARD
