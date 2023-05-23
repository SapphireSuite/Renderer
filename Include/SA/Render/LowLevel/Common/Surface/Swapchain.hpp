// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_COMMON_SWAPCHAIN_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace SA::RND
{
	class Swapchain
	{
	protected:
		Vec2ui mExtents;

	public:
		Vec2ui GetExtents() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_SWAPCHAIN_GUARD
