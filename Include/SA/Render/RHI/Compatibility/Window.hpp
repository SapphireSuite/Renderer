// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_WINDOW_GUARD
#define SAPPHIRE_RENDER_RHI_WINDOW_GUARD

#if defined(SA_WINDOWING_IMPL)

//#include <SA/Windowing/WHI/Window.hpp>

#else

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	#include <SA/Render/LowLevel/DX12/DX12API.hpp>
#endif

namespace SA::WND::WHI
{
	class Window
	{
	public:
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		virtual VkSurfaceKHR CreateVkSurfaceKHR(const SA::RND::VK::Instance& _instance) const = 0;
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
		virtual HWND GetHWNDHandle() const = 0;
#endif
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_WINDOW_GUARD
