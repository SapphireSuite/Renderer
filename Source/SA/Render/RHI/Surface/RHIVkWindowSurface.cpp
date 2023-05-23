// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHIVkWindowSurface.hpp>

#include <RHIRenderInterface.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkWindowSurface::Create(const RenderInterface* _renderIntf, const WND::WHI::Window* _window)
	{
		mHandle.Create(_renderIntf->API_Vulkan(), _window);
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

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL