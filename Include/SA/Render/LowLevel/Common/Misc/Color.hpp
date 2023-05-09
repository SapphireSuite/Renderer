// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COLOR_GUARD
#define SAPPHIRE_RENDER_COLOR_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#endif

namespace SA::RND
{
	struct Color
	{
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color black;
		static const Color white;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		operator VkClearValue() const noexcept;
		operator VkClearColorValue() const noexcept;

#endif
	};
}

#endif // SAPPHIRE_RENDER_COLOR_GUARD
