// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_IMAGE_BUFFER_INFO
#define SAPPHIRE_RENDER_VK_IMAGE_BUFFER_INFO

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#include <SA/Render/LowLevel/Common/Pass/PassAttachmentType.hpp>

namespace SA::RND::VK
{
	struct ImageBufferInfo
	{
		uint32_t imageFlags = 0u;
		VkImageType imageType = VK_IMAGE_TYPE_2D;
		VkImageViewType imageViewType = VK_IMAGE_VIEW_TYPE_2D;

		VkFormat format = VK_FORMAT_R8G8B8_UNORM;
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		VkSampleCountFlagBits sampling = VK_SAMPLE_COUNT_1_BIT;
		VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;

		VkImageUsageFlags usage = 0u;

		VkImageAspectFlags aspectFlags = 0u;

		VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkImageCreateInfo VkImageInfo() const noexcept;
		VkImageViewCreateInfo VkImageViewInfo(VkImage _image) const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_IMAGE_BUFFER_INFO
