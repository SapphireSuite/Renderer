// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SAMPLING_GUARD
#define SAPPHIRE_RENDER_RHI_SAMPLING_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class Sampling : uint8_t
		{
			/// no multisampling.
			Sample1Bit,

			/// 2 bits multisampling.
			Sample2Bits,

			/// 4 bits multisampling.
			Sample4Bits,

			/// 8 bits multisampling.
			Sample8Bits,

			/// 16 bits multisampling.
			Sample16Bits,

			/// 32 bits multisampling.
			Sample32Bits,

			/// 64 bits multisampling.
			Sample64Bits,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(RHI::Sampling _sampling);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		uint32_t API_GetSampleCount(RHI::Sampling _sampling);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SAMPLING_GUARD
