// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_FAMILY_MGR_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_FAMILY_MGR_GUARD

#include "VkQueue.hpp"
#include "VkQueueFamilyInfo.hpp"

namespace SA::RND::VK
{
	class Device;

	class QueueFamilyMgr
	{
		std::vector<Queue> mQueues;

	public:
	#if SA_DEBUG || SA_LOG_RELEASE_OPT
		std::string debugName;
	#endif

		void Create(const Device& _device, const QueueFamilyInfo& _info);
		void Destroy();

		const Queue& GetQueue(uint32_t _index) const;
		const Queue& operator[](uint32_t _index) const;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_FAMILY_MGR_GUARD
