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

#if SA_DEBUG
		VkMemoryPropertyFlags mMemoryPropertyFlags;
#endif

	public:
		/**
		* Create a GPU memory buffer.
		* 
		* @param[in] _src	Data to copy to the buffer. MemoryPropertyFlags must be `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT`
		*/
		void Create(const Device& _device,
			uint64_t _size,
			VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _memory,
			const void* _src = nullptr);
		void Destroy(const Device& _device);


		/**
		* Upload data from CPU to GPU Buffer.
		* MemoryPropertyFlags must contain `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT`
		*/
		void UploadData(const Device& _device, const void* _src, uint64_t _size, uint64_t _offset = 0u);

		/**
		* Read back data from GPU to CPU Buffer.
		* MemoryPropertyFlags must contain `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT`
		*/
		void ReadbackData(const Device& _device, void* _dst, uint64_t _size, uint64_t _offset = 0u);

		operator VkBuffer() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_BUFFER_GUARD
