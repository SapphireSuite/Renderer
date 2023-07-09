// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include "VkBufferBase.hpp"

namespace SA::RND::VK
{
	class Device;

	class Buffer : public BufferBase
	{
		VkBuffer mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mDeviceMemory = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, uint32_t _size, VkBufferUsageFlags _usage, VkMemoryPropertyFlags _memory);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_BUFFER_GUARD
