// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHISwapchainSettings.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::SwapchainSettings SwapchainSettings::API_Vulkan() const
	{
		VK::SwapchainSettings vkSettings;

		// Default values chosen by API.
		vkSettings.frameNum = frameNum;
		vkSettings.format = VK::API_GetFormat(format);

		return vkSettings;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::SwapchainSettings SwapchainSettings::API_DirectX12() const
	{
		DX12::SwapchainSettings d12Settings;

		d12Settings.frameNum = frameNum;

		if(format != Format::Unknown) // Let default value otherwise,
			d12Settings.format = DX12::API_GetFormat(format);

		return d12Settings;
	}

#endif
}
