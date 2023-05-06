// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_RENDER_DEVICE_INFO_GUARD

#include <string>
#include <cstdint>

namespace SA
{
	struct RenderDeviceInfo
	{
		/// Performance/Feature score used to sort devices.
		uint32_t score = 0;

		static bool SortByScore(const RenderDeviceInfo& _lhs, const RenderDeviceInfo& _rhs) noexcept;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_INFO_GUARD
