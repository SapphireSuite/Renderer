// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Texture/RHITextureUsage.hpp>

namespace SA::RND::VK
{
	VkImageUsageFlags API_GetTextureUsage(RHI::TextureUsage _usage)
	{
		VkImageUsageFlags vkUsage;

		// TODO: Warning check only one of Color and Depth is set.

		if (_usage & RHI::TextureUsageFlags::Color)
			vkUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (_usage & RHI::TextureUsageFlags::Depth)
			vkUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

		if (_usage & RHI::TextureUsageFlags::Input)
			vkUsage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		return vkUsage;
	}
}
