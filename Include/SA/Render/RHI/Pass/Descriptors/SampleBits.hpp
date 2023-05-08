// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SAMPLE_BITS_GUARD
#define SAPPHIRE_RENDER_RHI_SAMPLE_BITS_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class SampleBits : uint8_t
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


			/// Use maximum multisampling allowed by hardware.
			Max,

			Default = Sample8Bits,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(RHI::SampleBits _sampleBits);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SAMPLE_BITS_GUARD
