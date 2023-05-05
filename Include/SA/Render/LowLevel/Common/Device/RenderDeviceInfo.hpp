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
		std::string name;

		/// Device ID.
		uint32_t ID = uint32_t(-1);

		/// Vendor ID.
		uint32_t vendorID = uint32_t(-1);

		/// Performance/Feature score used to sort devices.
		uint32_t score = 0;

		static bool SortByScore(const RenderDeviceInfo& _lhs, const RenderDeviceInfo& _rhs) noexcept;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_INFO_GUARD
