// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_RHI_VK_COMMAND_POOL_GUARD

#include "RHICommandPool.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandPool.hpp>

namespace SA::RND::RHI
{
	class VkCommandPool : public CommandPool
	{
		VK::CommandPool mHandle;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

		const VK::CommandPool& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_COMMAND_POOL_GUARD
