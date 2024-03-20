// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Texture/RHITextureUsage.hpp>

namespace SA::RND::VK
{
	VkImageUsageFlags API_GetTextureUsage(uint8_t _usage)
	{
		VkImageUsageFlags usage;

		if (_usage & RHI::TextureUsage::RenderTarget)
			usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if(_usage & RHI::TextureUsage::Depth)
			usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

		if(_usage & RHI::TextureUsage::Input)
			usage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		return usage;
	}
}
