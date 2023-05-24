// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SWAPCHAIN_SETTINGS_BASE_GUARD
#define SAPPHIRE_RENDER_COMMON_SWAPCHAIN_SETTINGS_BASE_GUARD

#include <cstdint>

namespace SA::RND
{
	struct SwapchainSettingsBase
	{
		/**
		* Override frame number.
		* Default is -1 (optimized by API).
		*/
		uint32_t frameNum = uint32_t(-1);
	};
}

#endif // SAPPHIRE_RENDER_COMMON_SWAPCHAIN_SETTINGS_BASE_GUARD
