// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_FAMILY_INFO_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_FAMILY_INFO_GUARD

#include <vector>

#include "VkQueueInfo.hpp"

namespace SA::VK
{
	struct QueueFamilyInfo
	{
		std::vector<QueueInfo> queues;
	};

	struct QueueFamilyIndexInfo
	{
		uint32_t index = ~uint32_t();
		uint32_t num = 0u;
		
		std::vector<float> queuePriorities;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_FAMILY_INFO_GUARD
