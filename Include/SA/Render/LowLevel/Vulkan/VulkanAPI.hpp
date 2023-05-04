// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_API_GUARD
#define SAPPHIRE_RENDER_VULKAN_API_GUARD

/**
*	\file VulkanAPI.hpp
*
*	\brief \b vulkan.h support file.
*
*	\ingroup Render_Vulkan
*	\{
*/


#include <vulkan/vulkan.h>

#include "Debug/Debug.hpp"

/**
*	Useful Documentations:
* 
*	https://vulkan-tutorial.com/
*	https://developer.nvidia.com/blog/vulkan-dos-donts/
*/

#if SA_DEBUG || SA_LOG_RELEASE_OPT || defined(SA_DOXIGEN)

	/**
	 * \def SA_VK_API(_vkFunc, ...) 
	 * 
	 * \brief Sapphire Vulkan-specific API call macro.
	 * Helper macro to track Vulkan API calls and use
	 * Assertion macro with Exception_Vulkan/Exception_Default type and SA.Render.Vulkan.API channel.
	 * Input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _vkFunc	Vulkan function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_VK_API(_vkFunc, ...)\
	{\
		using RType = decltype(_vkFunc);\
	\
		[&]<typename T>(T)\
		{\
			if constexpr (std::is_same_v<RType, VkResult>)\
				SA_ASSERT((Vulkan, _vkFunc), SA.Render.Vulkan.API, ##__VA_ARGS__)\
			else if constexpr (std::is_same_v<RType, bool>)\
				SA_ASSERT((Default, _vkFunc), SA.Render.Vulkan.API, ##__VA_ARGS__)\
			else\
			{\
				_vkFunc;\
				SA_LOG(#_vkFunc, AssertSuccess, SA.Render.Vulkan.API, ##__VA_ARGS__)\
			}\
		}(0);\
	}

	/**
	 * Use templated lambda to force if constexpr branch-instantiation.
	 * Source: https://stackoverflow.com/questions/50051473/if-constexpr-in-c17-does-not-work-in-a-non-templated-function
	*/

#else

	// Execute Vk function without logging or assertion check.
	#define SA_VK_API(_vkFunc, ...) { _vkFunc; }

#endif

/** \} */

#endif // SAPPHIRE_RENDER_VULKAN_API_GUARD
