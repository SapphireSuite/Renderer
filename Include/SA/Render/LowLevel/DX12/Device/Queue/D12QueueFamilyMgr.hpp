// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_QUEUE_FAMILY_MGR_GUARD
#define SAPPHIRE_RENDER_D12_QUEUE_FAMILY_MGR_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct QueueFamilyInfo;

	class QueueFamilyMgr
	{
		std::vector<MComPtr<ID3D12CommandQueue>> mQueues;

	public:
	#if SA_DEBUG || SA_LOG_RELEASE_OPT
		std::string debugName;
	#endif

		void Create(const QueueFamilyInfo& _info);
		void Destroy();
		
		uint32_t GetQueueNum() const;

		ID3D12CommandQueue* GetQueue(uint32_t _index) const;
		ID3D12CommandQueue* operator[](uint32_t _index) const;
	};
}

#endif // SAPPHIRE_RENDER_D12_QUEUE_FAMILY_MGR_GUARD
