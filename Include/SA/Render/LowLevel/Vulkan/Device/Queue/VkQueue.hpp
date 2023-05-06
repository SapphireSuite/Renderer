// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include "VkQueueInfo.hpp"

namespace SA::VK
{
	class Device;

	class Queue
	{
		VkQueue mHandle = VK_NULL_HANDLE;

		uint32_t mFamilyIndex = ~uint32_t();

	public:
		uint32_t GetFamilyIndex() const noexcept;

		void Create(const Device& _device, const QueueInfo& _info);
		void Destroy();

		operator VkQueue() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_GUARD
