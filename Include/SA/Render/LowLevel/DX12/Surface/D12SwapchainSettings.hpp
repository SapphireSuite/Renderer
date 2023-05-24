// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_SWAPCHAIN_SETTINGS_GUARD
#define SAPPHIRE_RENDER_DX12_SWAPCHAIN_SETTINGS_GUARD

#include <SA/Render/LowLevel/Common/Surface/SwapchainSettingsBase.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct SwapchainSettings : public SwapchainSettingsBase
	{
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		SwapchainSettings() noexcept;
	};
}

#endif // SAPPHIRE_RENDER_DX12_SWAPCHAIN_SETTINGS_GUARD
