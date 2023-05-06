// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_MGR_INFO_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_MGR_INFO_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include "VkQueueFamilyInfo.hpp"

namespace SA::VK
{
	struct QueueMgrInfo
	{
		QueueFamilyInfo graphics;
		QueueFamilyInfo compute;
		QueueFamilyInfo transfer;
		QueueFamilyInfo present;
	};

	struct QueueMgrIndexInfo
	{
		std::vector<QueueFamilyIndexInfo> familyInfos;

		std::vector<VkDeviceQueueCreateInfo> GetQueueCreateInfos() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_MGR_INFO_GUARD
