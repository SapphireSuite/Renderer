// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/VkWindowSurface.hpp>

namespace SA::VK
{
	WindowSurface::operator VkSurfaceKHR() const
	{
		return mHandle;
	}	
}
