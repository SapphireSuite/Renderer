// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_IWINDOW_INTERFACE_GUARD
#define SAPPHIRE_RENDER_RHI_IWINDOW_INTERFACE_GUARD

#if defined(SA_WINDOWING_IMPL)

//#include <SA/Windowing/WHI/WindowInterface.hpp>

#else

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	#include <SA/Render/LowLevel/DX12/DX12API.hpp>
#endif

namespace SA::RND::RHI
{
	class IWindowInterface
	{
	public:
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		inline virtual std::vector<const char*> QueryRequiredExtensions() const { return std::vector<const char*>(); }

#endif
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_IWINDOW_INTERFACE_GUARD
