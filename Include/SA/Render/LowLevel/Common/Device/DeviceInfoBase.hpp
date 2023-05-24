// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEVICE_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_DEVICE_INFO_BASE_GUARD

#include <string>
#include <cstdint>

#include "QueueRequirements.hpp" // @rmaxime: required in children classes.

namespace SA::RND
{
	struct DeviceInfoBase
	{
		/// Performance/Feature score used to sort devices.
		uint32_t score = 0;

		/// Sort by descending-order score
		static bool SortByScore(const DeviceInfoBase& _lhs, const DeviceInfoBase& _rhs) noexcept;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_INFO_BASE_GUARD
