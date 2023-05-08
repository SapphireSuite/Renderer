// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueueMgr.hpp>

namespace SA::RND::VK
{
	QueueMgr::QueueMgr()
	{
	#if SA_DEBUG || SA_LOG_RELEASE_OPT
		graphics.debugName = "Graphics";
		compute.debugName = "Compute";
		transfer.debugName = "Transfer";
		present.debugName = "Present";
	#endif
	}

	void QueueMgr::Create(const Device& _device, const QueueMgrInfo& _info)
	{
		graphics.Create(_device, _info.graphics);
		compute.Create(_device, _info.compute);
		transfer.Create(_device, _info.transfer);
		present.Create(_device, _info.present);

		SA_LOG(L"Queue Mgr created", Info, SA.Render.Vulkan);
	}
	
	void QueueMgr::Destroy()
	{
		graphics.Destroy();
		compute.Destroy();
		transfer.Destroy();
		present.Destroy();

		SA_LOG(L"Queue Mgr destroyed", Info, SA.Render.Vulkan);
	}
}
