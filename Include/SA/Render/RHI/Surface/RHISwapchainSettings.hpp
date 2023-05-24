// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SWAPCHAIN_SETTINGS_GUARD
#define SAPPHIRE_RENDER_RHI_SWAPCHAIN_SETTINGS_GUARD

#include <SA/Render/LowLevel/Common/Surface/SwapchainSettingsBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Surface/VkSwapchainSettings.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/Surface/D12SwapchainSettings.hpp>

#endif


#include <SA/Render/RHI/Misc/Format.hpp>

namespace SA::RND
{
	namespace RHI
	{
		struct SwapchainSettings : public SwapchainSettingsBase
		{
			/**
			* Overridden format.
			* Default is chosen by API for optimization.
			*/
			Format format = Format::Unknown;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			VK::SwapchainSettings API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			DX12::SwapchainSettings API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_SWAPCHAIN_SETTINGS_GUARD
