// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/DeviceInfo.hpp>

namespace SA::RND
{
	bool DeviceInfo::SortByScore(const DeviceInfo& _lhs, const DeviceInfo& _rhs) noexcept
	{
		return _lhs.score > _rhs.score;
	}
}
