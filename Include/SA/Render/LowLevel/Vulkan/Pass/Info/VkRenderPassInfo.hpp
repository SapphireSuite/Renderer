// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>
#include <SA/Render/LowLevel/Vulkan/Texture/VkTextureDescriptor.hpp>

namespace SA::RND::VK
{
	using AttachmentInfo = SA::RND::AttachmentInfo<Texture>;
	using SubpassInfo = SA::RND::SubpassInfo<Texture>;
	using RenderPassInfo = SA::RND::RenderPassInfo<Texture, TextureDescriptor>;
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
