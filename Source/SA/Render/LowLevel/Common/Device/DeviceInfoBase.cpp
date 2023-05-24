// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/DeviceInfoBase.hpp>

namespace SA::RND
{
	bool DeviceInfoBase::SortByScore(const DeviceInfoBase& _lhs, const DeviceInfoBase& _rhs) noexcept
	{
		return _lhs.score > _rhs.score;
	}
}
