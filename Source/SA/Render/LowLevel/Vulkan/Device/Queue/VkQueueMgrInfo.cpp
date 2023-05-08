// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueueMgrInfo.hpp>

namespace SA::RND::VK
{
	std::vector<VkDeviceQueueCreateInfo> QueueMgrIndexInfo::GetQueueCreateInfos() const
	{
		std::vector<VkDeviceQueueCreateInfo> result;
		result.reserve(familyInfos.size());

		for (auto& famIndexInfo : familyInfos)
		{
			VkDeviceQueueCreateInfo queueInfos{};
			queueInfos.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfos.pNext = nullptr;
			queueInfos.flags = 0;
			queueInfos.queueFamilyIndex = famIndexInfo.index;
			queueInfos.queueCount = famIndexInfo.num;
			queueInfos.pQueuePriorities = famIndexInfo.queuePriorities.data();

			result.emplace_back(queueInfos);
		}

		return result;
	}
}
