// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_INFO_GUARD

#include <cstdint>

namespace SA::RND::VK
{
	struct QueueInfo
	{
		uint32_t familyIndex = 0;
		uint32_t queueIndex = 0;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_INFO_GUARD
