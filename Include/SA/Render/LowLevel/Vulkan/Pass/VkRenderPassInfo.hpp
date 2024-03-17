// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::VK
{
	using RenderPassInfo = SA::RND::RenderPassInfo<Texture>;
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
