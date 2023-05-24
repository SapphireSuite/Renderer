// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SWAPCHAIN_BASE_GUARD
#define SAPPHIRE_RENDER_COMMON_SWAPCHAIN_BASE_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace SA::RND
{
	class SwapchainBase
	{
	protected:
		Vec2ui mExtents;

	public:
		const Vec2ui& GetExtents() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_SWAPCHAIN_BASE_GUARD
