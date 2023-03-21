// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_Vulkan.hpp"

#define SA_VK_VALIDATION_LAYERS (SA_DEBUG || SA_RENDER_VALIDATION_LAYER_RELEASE)

#if SA_DEBUG || SA_LOG_RELEASE_OPT || defined(SA_DOXIGEN)

	/**
	 * \def SA_VK_ASSERT(_vkFunc, ...) 
	 * 
	 * \brief Sapphire Vulkan-specific assertion macro.
	 * Helper macro to use Assertion macro with Exception_Vulkan type and SA.Render.Vulkan channel
	 * The input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _vkFunc	Vulkan function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_VK_ASSERT(_vkFunc, ...) SA_ASSERT((Vulkan, _vkFunc), SA.Render.Vulkan, ##__VA_ARGS__)

#else

	// Execute Vk function without logging.
	#define SA_VK_ASSERT(_vkFunc, ...) { _vkFunc; }

#endif

#endif // SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
