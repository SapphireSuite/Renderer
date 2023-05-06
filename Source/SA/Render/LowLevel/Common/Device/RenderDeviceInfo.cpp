// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RenderDeviceInfo.hpp>

namespace SA
{
	bool RenderDeviceInfo::SortByScore(const RenderDeviceInfo& _lhs, const RenderDeviceInfo& _rhs) noexcept
	{
		return _lhs.score > _rhs.score;
	}
}
