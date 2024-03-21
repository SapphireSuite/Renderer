// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHIVkWindowSurface.hpp>

#include <RHIVkRenderInterface.hpp>

namespace SA::RND::RHI
{
	void VkWindowSurface::Create(const RenderInterface* _renderIntf, const IRenderWindow* _window)
	{
		mHandle.Create(_window->CreateVkSurfaceKHR(_renderIntf->API_Vulkan()));
	}

	void VkWindowSurface::Destroy(const RenderInterface* _renderIntf)
	{
		mHandle.Destroy(_renderIntf->API_Vulkan());
	}


	const VK::WindowSurface& VkWindowSurface::API_Vulkan() const
	{
		return mHandle;
	}
}
