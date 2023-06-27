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

		const VK::Device* mVkDevice = nullptr;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

	//{ Allocation
		
		// TODO: Add Command PRIMARY/SECONDARY parameter.
		CommandBuffer* Allocate() override final;
		std::vector<CommandBuffer*> Allocate(uint32_t _num) override final;

		void Free(CommandBuffer* _cmd) override final;
		void Free(std::vector<CommandBuffer*>& _cmds) override final;

	//}

		const VK::CommandPool& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_COMMAND_POOL_GUARD
