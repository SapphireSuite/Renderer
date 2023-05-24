// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_LOGICAL_DEVICE_GUARD
#define SAPPHIRE_RENDER_D12_LOGICAL_DEVICE_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	using LogicalDevice = Microsoft::WRL::ComPtr<ID3D12Device>;
}

#endif // SAPPHIRE_RENDER_D12_LOGICAL_DEVICE_GUARD
