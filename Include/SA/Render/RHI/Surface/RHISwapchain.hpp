// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_RHI_SWAPCHAIN_GUARD

#include "RHISwapchainSettings.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Swapchain;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Swapchain;
	}

#endif

	namespace RHI
	{
		class RenderInterface;
		class Device;
		class WindowSurface;

		class Swapchain
		{
		public:
			virtual ~Swapchain() = default;

			virtual void Create(const RenderInterface* _renderIntf,
				const Device* _device,
				const WindowSurface* _winSurface,
				const SwapchainSettings& _settings) = 0;
			virtual void Destroy(const RenderInterface* _renderIntf, const Device* _device) = 0;
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_SWAPCHAIN_GUARD
