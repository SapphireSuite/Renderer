// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_INSTANCE_GUARD
#define SAPPHIRE_RENDER_VK_INSTANCE_GUARD

#include <vector>

#include "VulkanAPI.hpp"

namespace SA
{
	namespace VK
	{
		class Instance
		{
			VkInstance mHandle = VK_NULL_HANDLE;

	#if SA_VK_VALIDATION_LAYERS

			VkDebugUtilsMessengerEXT mDebugMessenger = nullptr;

	#endif

		public:
			void Create(std::vector<const char*> _extensions = std::vector<const char*>());
			void Destroy();

			operator VkInstance() const noexcept;
		};
	}
}

#endif // SAPPHIRE_RENDER_VK_INSTANCE_GUARD
