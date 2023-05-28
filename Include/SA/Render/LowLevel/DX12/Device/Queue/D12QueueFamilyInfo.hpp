// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_QUEUE_FAMILY_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_QUEUE_FAMILY_INFO_GUARD

#include <vector>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct QueueFamilyInfo
	{
		D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		std::vector<MComPtr<ID3D12CommandQueue>> queues;
	};
}

#endif // SAPPHIRE_RENDER_DX12_QUEUE_FAMILY_INFO_GUARD
