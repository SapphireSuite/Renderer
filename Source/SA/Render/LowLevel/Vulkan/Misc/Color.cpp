// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

namespace SA::RND
{
	Color::operator VkClearValue() const noexcept
	{
		return VkClearValue{ VkClearColorValue{ { r, g, b, a } } };
	}

	Color::operator VkClearColorValue() const noexcept
	{
		return VkClearColorValue{ { r, g, b, a} };
	}
}
