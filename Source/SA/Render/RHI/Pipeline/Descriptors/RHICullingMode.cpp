// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptors/RHICullingMode.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(RHI::CullingMode _mode)
		{
			static constexpr VkCullModeFlags vkCullModeIndexMap[] = {
				VK_CULL_MODE_NONE,
				VK_CULL_MODE_FRONT_BIT,
				VK_CULL_MODE_BACK_BIT
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkCullModeIndexMap)), SA.Render.RHI.Vulkan,
				(L"CullingMode value [%1] invalid", index));

			return vkCullModeIndexMap[index];
		}
	}

#endif
}
