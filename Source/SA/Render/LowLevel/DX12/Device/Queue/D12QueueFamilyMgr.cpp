// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/D12QueueFamilyMgr.hpp>

#include <Device/Queue/D12QueueFamilyInfo.hpp>

namespace SA::RND::DX12
{
	void QueueFamilyMgr::Create(const QueueFamilyInfo& _info)
	{
		mQueues = _info.queues;	

		SA_LOG((L"%1 Queue Family Manager created", debugName), Info, SA.Render.DX12);
	}
	
	void QueueFamilyMgr::Destroy()
	{
		mQueues.clear();

		SA_LOG((L"%1 Queue Family Manager destroyed", debugName), Info, SA.Render.DX12);
	}
	
	
	uint32_t QueueFamilyMgr::GetQueueNum() const
	{
		return static_cast<uint32_t>(mQueues.size());
	}

	
	ID3D12CommandQueue* QueueFamilyMgr::GetQueue(uint32_t _index) const
	{
		SA_ASSERT((OutOfArrayRange, _index, mQueues), SA.Render.DX12, L"Queue index out of family range");

		return mQueues[_index].Get();
	}
	
	ID3D12CommandQueue* QueueFamilyMgr::operator[](uint32_t _index) const
	{
		return GetQueue(_index);
	}
}
