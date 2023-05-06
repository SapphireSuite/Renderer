// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_MGR_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_MGR_GUARD

#include "VkQueueFamilyMgr.hpp"
#include "VkQueueMgrInfo.hpp"

namespace SA::VK
{
	class Device;

	class QueueMgr
	{
	public:
		QueueFamilyMgr graphics;
		QueueFamilyMgr compute;
		QueueFamilyMgr transfer;
		QueueFamilyMgr present;

		QueueMgr();

		void Create(const Device& _device, const QueueMgrInfo& _info);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_MGR_GUARD
