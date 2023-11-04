// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class Buffer;

	class CommandBuffer
	{
		friend class CommandPool;

		VkCommandBuffer mHandle = VK_NULL_HANDLE;

	public:
		void Begin();
		void End();

		void CopyBuffer(const Buffer& _src, Buffer& _dst, uint64_t _size, uint64_t _srcOffset = 0u, uint64_t _dstOffset = 0u);

		void Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance);

		operator VkCommandBuffer() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD
