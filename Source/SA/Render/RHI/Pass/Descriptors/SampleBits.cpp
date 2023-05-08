// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/SampleBits.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(RHI::SampleBits _sampleBits)
		{
			static constexpr VkSampleCountFlagBits vkSampleCountIndexMap[] = {
				VK_SAMPLE_COUNT_1_BIT,
				VK_SAMPLE_COUNT_2_BIT,
				VK_SAMPLE_COUNT_4_BIT,
				VK_SAMPLE_COUNT_8_BIT,
				VK_SAMPLE_COUNT_16_BIT,
				VK_SAMPLE_COUNT_32_BIT,
				VK_SAMPLE_COUNT_64_BIT,
				VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM
			};

			const uint8_t index = static_cast<uint8_t>(_sampleBits);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkSampleCountIndexMap)), SA.Render.RHI.Vulkan,
				(L"SampleBits value [%1] invalid", index));

			return vkSampleCountIndexMap[index];
		}
	}

#endif
}
