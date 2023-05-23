// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHIVkSwapchain.hpp>

#include <Device/RHIDevice.hpp>
#include <Surface/RHIWindowSurface.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkSwapchain::Create(const RenderInterface* _renderIntf,
		const Device* _device,
		const WindowSurface* _winSurface,
		const SwapchainSettings& _settings)
	{
		(void)_renderIntf;
		mHandle.Create(_device->API_Vulkan(), _winSurface->API_Vulkan(), _settings.API_Vulkan());
	}

	void VkSwapchain::Destroy(const RenderInterface* _renderIntf, const Device* _device)
	{
		(void)_renderIntf;
		mHandle.Destroy(_device->API_Vulkan());
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
