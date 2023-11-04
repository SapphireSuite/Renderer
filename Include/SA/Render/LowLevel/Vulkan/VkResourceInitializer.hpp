// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_VK_RESOURCE_INITIALIZER_GUARD

#include "Device/Command/VkCommandPool.hpp"

namespace SA::RND::VK
{
	class Device;
	class Queue;
	class Buffer;

	class ResourceInitializer
	{
		CommandPool mCmdPool;
		const Queue* mQueue = nullptr;

		std::list<Buffer> mStagingBuffers;

	public:
		CommandBuffer cmd;

		void Create(const Device& _device);
		void Create(const Device& _device, const Queue& _queue);
		void Destroy(const Device& _device);

		Buffer& CreateStagingBuffer(const Device& _device, uint64_t _size, const void* _data = nullptr);

		void Submit(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_RESOURCE_INITIALIZER_GUARD
