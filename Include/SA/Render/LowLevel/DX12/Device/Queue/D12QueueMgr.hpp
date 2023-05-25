// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_QUEUE_MGR_GUARD
#define SAPPHIRE_RENDER_D12_QUEUE_MGR_GUARD

#include "D12QueueFamilyMgr.hpp"

namespace SA::RND::DX12
{
	struct DeviceInfo;

	class QueueMgr
	{
	public:
		QueueFamilyMgr graphics;
		QueueFamilyMgr compute;
		QueueFamilyMgr transfer;
		QueueFamilyMgr present;

		QueueMgr();

		void Create(const DeviceInfo& _info);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_D12_QUEUE_MGR_GUARD
