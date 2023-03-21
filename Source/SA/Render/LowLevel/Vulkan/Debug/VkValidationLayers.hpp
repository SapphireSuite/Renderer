// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_VALIDATION_LAYERS_GUARD
#define SAPPHIRE_RENDER_VK_VALIDATION_LAYERS_GUARD

#include <VulkanAPI.hpp>

#if SA_VK_VALIDATION_LAYERS || defined(SA_DOXYGEN)

namespace SA
{
	namespace VK
	{
		class ValidationLayers
		{
		public:
			~ValidationLayers() = delete;

			static VkDebugUtilsMessengerCreateInfoEXT GetDebugUtilsMessengerCreateInfo() noexcept;

			static uint32_t GetLayerNum() noexcept;
			static const char* const* GetLayerNames() noexcept;

			static bool CheckValidationSupport() noexcept;

			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData);
		};
	}
}

#endif

#endif // SAPPHIRE_RENDER_VK_VALIDATION_LAYERS_GUARD
