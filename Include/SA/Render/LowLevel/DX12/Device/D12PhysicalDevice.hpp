// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_PHYSICAL_DEVICE_GUARD
#define SAPPHIRE_RENDER_D12_PHYSICAL_DEVICE_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	using PhysicalDevice = Microsoft::WRL::ComPtr<IDXGIAdapter3>;
}

#endif // SAPPHIRE_RENDER_D12_PHYSICAL_DEVICE_GUARD
