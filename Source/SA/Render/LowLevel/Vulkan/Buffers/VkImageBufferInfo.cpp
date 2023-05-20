// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/VkImageBufferInfo.hpp>

namespace SA::RND::VK
{
	VkImageCreateInfo ImageBufferInfo::VkImageInfo() const noexcept
	{
		VkImageCreateInfo vkInfos{};
		vkInfos.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		vkInfos.pNext = nullptr;
		
		vkInfos.flags = imageFlags;
		
		if(imageType == VK_IMAGE_TYPE_3D)
			vkInfos.flags |= VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

		vkInfos.imageType = imageType;
		vkInfos.format = format;
		vkInfos.extent = VkExtent3D{ extents.x, extents.y, 1 };
		vkInfos.mipLevels = mipLevels;
		vkInfos.arrayLayers = imageType == VK_IMAGE_TYPE_3D ? 6u : 1u;;
		
		vkInfos.samples = sampling;
		vkInfos.tiling = tiling;

		vkInfos.usage = usage;

		vkInfos.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		vkInfos.queueFamilyIndexCount = 0u;
		vkInfos.pQueueFamilyIndices = nullptr;
		vkInfos.initialLayout = initialLayout;

		return vkInfos;
	}

	VkImageViewCreateInfo ImageBufferInfo::VkImageViewInfo(VkImage _image) const noexcept
	{
		VkImageViewCreateInfo vkInfos{};
		vkInfos.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		vkInfos.pNext = nullptr;
		vkInfos.flags = 0;
		vkInfos.image = _image;
		vkInfos.viewType = imageViewType;
		vkInfos.format = format;

		vkInfos.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		vkInfos.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		vkInfos.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		vkInfos.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		vkInfos.subresourceRange.aspectMask = aspectFlags;
		vkInfos.subresourceRange.baseMipLevel = 0u;
		vkInfos.subresourceRange.levelCount = mipLevels;
		vkInfos.subresourceRange.baseArrayLayer = 0u;
		
		vkInfos.subresourceRange.layerCount = 1u;

		if(imageViewType == VK_IMAGE_VIEW_TYPE_CUBE || imageViewType == VK_IMAGE_VIEW_TYPE_CUBE_ARRAY)
			vkInfos.subresourceRange.layerCount = 6u;

		return vkInfos;
	}
}
