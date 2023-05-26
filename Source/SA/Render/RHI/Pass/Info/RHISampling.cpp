// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHISampling.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(RHI::Sampling _sampling)
		{
			static constexpr VkSampleCountFlagBits vkSampleCountIndexMap[] = {
				VK_SAMPLE_COUNT_1_BIT,
				VK_SAMPLE_COUNT_2_BIT,
				VK_SAMPLE_COUNT_4_BIT,
				VK_SAMPLE_COUNT_8_BIT,
				VK_SAMPLE_COUNT_16_BIT,
				VK_SAMPLE_COUNT_32_BIT,
				VK_SAMPLE_COUNT_64_BIT
			};

			const uint8_t index = static_cast<uint8_t>(_sampling);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkSampleCountIndexMap)), SA.Render.RHI.Vulkan,
				(L"Sampling value [%1] invalid", index));

			return vkSampleCountIndexMap[index];
		}
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		uint32_t API_GetSampleCount(RHI::Sampling _sampling)
		{
			static constexpr uint32_t dx12SampleCountIndexMap[] = {
				1,
				2,
				4,
				8,
				16,
				32,
				64
			};

			const uint8_t index = static_cast<uint8_t>(_sampling);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(dx12SampleCountIndexMap)), SA.Render.RHI.DX12,
				(L"Sampling value [%1] invalid", index));

			return dx12SampleCountIndexMap[index];
		}
	}

#endif
}