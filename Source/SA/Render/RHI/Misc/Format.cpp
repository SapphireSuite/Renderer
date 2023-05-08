// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Misc/Format.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkFormat API_GetFormat(RHI::Format _format)
		{
			static const VkFormat vkFormatIndexMap[] = {
				VK_FORMAT_R8_UNORM,
				VK_FORMAT_R8_SNORM,
				VK_FORMAT_R8_USCALED,
				VK_FORMAT_R8_SSCALED,
				VK_FORMAT_R8_UINT,
				VK_FORMAT_R8_SINT,
				VK_FORMAT_R8_SRGB,

				VK_FORMAT_R8G8_UNORM,
				VK_FORMAT_R8G8_SNORM,
				VK_FORMAT_R8G8_USCALED,
				VK_FORMAT_R8G8_SSCALED,
				VK_FORMAT_R8G8_UINT,
				VK_FORMAT_R8G8_SINT,
				VK_FORMAT_R8G8_SRGB,

				VK_FORMAT_R8G8B8_UNORM,
				VK_FORMAT_R8G8B8_SNORM,
				VK_FORMAT_R8G8B8_USCALED,
				VK_FORMAT_R8G8B8_SSCALED,
				VK_FORMAT_R8G8B8_UINT,
				VK_FORMAT_R8G8B8_SINT,
				VK_FORMAT_R8G8B8_SRGB,

				VK_FORMAT_B8G8R8_UNORM,
				VK_FORMAT_B8G8R8_SNORM,
				VK_FORMAT_B8G8R8_USCALED,
				VK_FORMAT_B8G8R8_SSCALED,
				VK_FORMAT_B8G8R8_UINT,
				VK_FORMAT_B8G8R8_SINT,
				VK_FORMAT_B8G8R8_SRGB,

				VK_FORMAT_R8G8B8A8_UNORM,
				VK_FORMAT_R8G8B8A8_SNORM,
				VK_FORMAT_R8G8B8A8_USCALED,
				VK_FORMAT_R8G8B8A8_SSCALED,
				VK_FORMAT_R8G8B8A8_UINT,
				VK_FORMAT_R8G8B8A8_SINT,
				VK_FORMAT_R8G8B8A8_SRGB,

				VK_FORMAT_B8G8R8A8_UNORM,
				VK_FORMAT_B8G8R8A8_SNORM,
				VK_FORMAT_B8G8R8A8_USCALED,
				VK_FORMAT_B8G8R8A8_SSCALED,
				VK_FORMAT_B8G8R8A8_UINT,
				VK_FORMAT_B8G8R8A8_SINT,
				VK_FORMAT_B8G8R8A8_SRGB,

				VK_FORMAT_R16_UNORM,
				VK_FORMAT_R16_SNORM,
				VK_FORMAT_R16_USCALED,
				VK_FORMAT_R16_SSCALED,
				VK_FORMAT_R16_UINT,
				VK_FORMAT_R16_SINT,
				VK_FORMAT_R16_SFLOAT,

				VK_FORMAT_R16G16_UNORM,
				VK_FORMAT_R16G16_SNORM,
				VK_FORMAT_R16G16_USCALED,
				VK_FORMAT_R16G16_SSCALED,
				VK_FORMAT_R16G16_UINT,
				VK_FORMAT_R16G16_SINT,
				VK_FORMAT_R16G16_SFLOAT,

				VK_FORMAT_R16G16B16_UNORM,
				VK_FORMAT_R16G16B16_SNORM,
				VK_FORMAT_R16G16B16_USCALED,
				VK_FORMAT_R16G16B16_SSCALED,
				VK_FORMAT_R16G16B16_UINT,
				VK_FORMAT_R16G16B16_SINT,
				VK_FORMAT_R16G16B16_SFLOAT,

				VK_FORMAT_R16G16B16A16_UNORM,
				VK_FORMAT_R16G16B16A16_SNORM,
				VK_FORMAT_R16G16B16A16_USCALED,
				VK_FORMAT_R16G16B16A16_SSCALED,
				VK_FORMAT_R16G16B16A16_UINT,
				VK_FORMAT_R16G16B16A16_SINT,
				VK_FORMAT_R16G16B16A16_SFLOAT,

				VK_FORMAT_R32_UINT,
				VK_FORMAT_R32_SINT,
				VK_FORMAT_R32_SFLOAT,

				VK_FORMAT_R32G32_UINT,
				VK_FORMAT_R32G32_SINT,
				VK_FORMAT_R32G32_SFLOAT,

				VK_FORMAT_R32G32B32_UINT,
				VK_FORMAT_R32G32B32_SINT,
				VK_FORMAT_R32G32B32_SFLOAT,

				VK_FORMAT_R32G32B32A32_UINT,
				VK_FORMAT_R32G32B32A32_SINT,
				VK_FORMAT_R32G32B32A32_SFLOAT,

				VK_FORMAT_R64_UINT,
				VK_FORMAT_R64_SINT,
				VK_FORMAT_R64_SFLOAT,
				
				VK_FORMAT_R64G64_UINT,
				VK_FORMAT_R64G64_SINT,
				VK_FORMAT_R64G64_SFLOAT,

				VK_FORMAT_R64G64B64_UINT,
				VK_FORMAT_R64G64B64_SINT,
				VK_FORMAT_R64G64B64_SFLOAT,

				VK_FORMAT_R64G64B64A64_UINT,
				VK_FORMAT_R64G64B64A64_SINT,
				VK_FORMAT_R64G64B64A64_SFLOAT,
			};

			const uint32_t index = static_cast<uint32_t>(_format);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkFormatIndexMap)), SA.Render.RHI.Vulkan,
				(L"Format value [%1] invalid", index));

			return vkFormatIndexMap[index];
		}
	}

#endif
}
