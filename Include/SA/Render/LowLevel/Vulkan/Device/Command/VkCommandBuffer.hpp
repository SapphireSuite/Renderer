// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::VK
{
	class CommandBuffer
	{
		friend class CommandPool;

		VkCommandBuffer mHandle = VK_NULL_HANDLE;

	public:
		void Begin();
		void End();

		operator VkCommandBuffer() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD
