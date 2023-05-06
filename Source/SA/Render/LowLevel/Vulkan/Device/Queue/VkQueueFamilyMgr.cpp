// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueueFamilyMgr.hpp>

namespace SA::VK
{
	void QueueFamilyMgr::Create(const Device& _device, const QueueFamilyInfo& _info)
	{
		mQueues.resize(_info.queues.size());

		for (uint32_t i = 0u; i < _info.queues.size(); ++i)
			mQueues[i].Create(_device, _info.queues[i]);

		SA_LOG((L"%1 Queue Family Manager created", debugName), Info, SA.Render.Vulkan);
	}
	
	void QueueFamilyMgr::Destroy()
	{
		for(auto& queue : mQueues)
			queue.Destroy();
		
		mQueues.clear();

		SA_LOG((L"%1 Queue Family Manager destroyed", debugName), Info, SA.Render.Vulkan);
	}


	const Queue& QueueFamilyMgr::GetQueue(uint32_t _index) const
	{
		SA_ASSERT((OutOfArrayRange, _index, mQueues), SA.Render.Vulkan, L"Queue index out of family range");

		return mQueues[_index];
	}

	const Queue& QueueFamilyMgr::operator[](uint32_t _index) const
	{
		return GetQueue(_index);
	}
}
