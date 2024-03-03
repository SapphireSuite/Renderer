// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SAMPLING_GUARD
#define SAPPHIRE_RENDER_COMMON_SAMPLING_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	enum class Sampling : uint8_t
	{
		/// no multisampling.
		S1Bit = (1 << 0),

		/// 2 bits multisampling.
		S2Bits = (1 << 1),

		/// 4 bits multisampling.
		S4Bits = (1 << 2),

		/// 8 bits multisampling.
		S8Bits = (1 << 3),

		/// 16 bits multisampling.
		S16Bits = (1 << 4),

		/// 32 bits multisampling.
		S32Bits = (1 << 5),

		/// 64 bits multisampling.
		S64Bits = (1 << 6),
	};

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampling(Sampling _sampling);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		uint32_t API_GetSampling(Sampling _sampling);
	}

#endif
}

#endif // SAPPHIRE_RENDER_COMMON_SAMPLING_GUARD
