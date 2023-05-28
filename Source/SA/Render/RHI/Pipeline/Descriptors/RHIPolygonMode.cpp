// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptors/RHIPolygonMode.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkPolygonMode API_GetPolygonMode(RHI::PolygonMode _mode)
		{
			static constexpr VkPolygonMode vkPolygonModeIndexMap[] = {
				VK_POLYGON_MODE_POINT,
				VK_POLYGON_MODE_LINE,
				VK_POLYGON_MODE_FILL
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkPolygonModeIndexMap)), SA.Render.RHI.Vulkan,
				(L"CullingMode value [%1] invalid", index));

			return vkPolygonModeIndexMap[index];
		}
	}

#endif
}
