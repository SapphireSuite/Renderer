// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Misc/Format.hpp>

namespace SA::RND::VK
{
	static const VkFormat vkFormatIndexMap[] = {
		VK_FORMAT_UNDEFINED,

		VK_FORMAT_R8_UNORM,
		VK_FORMAT_R8_SNORM,
		VK_FORMAT_R8_UINT,
		VK_FORMAT_R8_SINT,

		VK_FORMAT_R8G8_UNORM,
		VK_FORMAT_R8G8_SNORM,
		VK_FORMAT_R8G8_UINT,
		VK_FORMAT_R8G8_SINT,

		VK_FORMAT_R8G8B8A8_UNORM,
		VK_FORMAT_R8G8B8A8_SNORM,
		VK_FORMAT_R8G8B8A8_UINT,
		VK_FORMAT_R8G8B8A8_SINT,
		VK_FORMAT_R8G8B8A8_SRGB,

		VK_FORMAT_B8G8R8A8_UNORM,
		VK_FORMAT_B8G8R8A8_SNORM,
		VK_FORMAT_B8G8R8A8_UINT,
		VK_FORMAT_B8G8R8A8_SINT,
		VK_FORMAT_B8G8R8A8_SRGB,

		VK_FORMAT_R16_UNORM,
		VK_FORMAT_R16_SNORM,
		VK_FORMAT_R16_UINT,
		VK_FORMAT_R16_SINT,
		VK_FORMAT_R16_SFLOAT,

		VK_FORMAT_R16G16_UNORM,
		VK_FORMAT_R16G16_SNORM,
		VK_FORMAT_R16G16_UINT,
		VK_FORMAT_R16G16_SINT,
		VK_FORMAT_R16G16_SFLOAT,

		VK_FORMAT_R16G16B16A16_UNORM,
		VK_FORMAT_R16G16B16A16_SNORM,
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

		VK_FORMAT_D16_UNORM,
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D24_UNORM_S8_UINT,
	};

	VkFormat API_GetFormat(Format _format)
	{
		const uint32_t index = static_cast<uint32_t>(_format);

		SA_ASSERT((OutOfRange, index, 0u, sizeof(vkFormatIndexMap)), SA.Render.RHI.Vulkan,
			(L"Format value [%1] invalid", index));

		return vkFormatIndexMap[index];
	}

	Format API_GetFormat(VkFormat _vkFormat)
	{
		for(uint32_t i = 0; i < sizeof(vkFormatIndexMap); ++i)
		{
			if(vkFormatIndexMap[i] == _vkFormat)
				return static_cast<Format>(i);
		}

		SA_LOG((L"VkFormat [%1] not supported yet!", static_cast<uint32_t>(_vkFormat)), Error, Sa.Render.RHI.Vulkan);

		return Format::R8G8B8A8_UNORM;
	}

	VkFormat SRGBToUNORMFormat(VkFormat _vkFormat) noexcept
	{
		if (_vkFormat == VK_FORMAT_R8G8B8A8_SRGB)
			return VK_FORMAT_R8G8B8A8_UNORM;

		if (_vkFormat == VK_FORMAT_B8G8R8A8_SRGB)
			return VK_FORMAT_B8G8R8A8_UNORM;

		return _vkFormat;
	}

	bool IsPresentFormat(VkFormat _vkFormat) noexcept
	{
		return _vkFormat == VK_FORMAT_R8G8B8A8_SRGB || _vkFormat == VK_FORMAT_B8G8R8A8_SRGB;
	}
}
