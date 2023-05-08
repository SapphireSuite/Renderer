// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_DEVICE_INFO_GUARD

#include <string>
#include <cstdint>

namespace SA::RND
{
	struct DeviceInfo
	{
		/// Performance/Feature score used to sort devices.
		uint32_t score = 0;

		/// Sort by descending-order score
		static bool SortByScore(const DeviceInfo& _lhs, const DeviceInfo& _rhs) noexcept;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_INFO_GUARD
