// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct TextureDescriptor
	{
		Vec2ui extents;

		VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;

		VkSampleCountFlagBits sampling = VK_SAMPLE_COUNT_1_BIT;

		VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		Color clearColor = Color::black;
	};
}

#endif // SAPPHIRE_RENDER_VK_TEXTURE_DESCRIPTOR_GUARD