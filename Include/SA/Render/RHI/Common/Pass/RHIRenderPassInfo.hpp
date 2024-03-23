// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/RHI/Common/Misc/RHISampling.hpp>
#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>

namespace SA::RND::RHI
{
	using AttachmentInfo = SA::RND::AttachmentInfo<Texture>;
	using SubpassInfo = SA::RND::SubpassInfo<Texture>;
	using RenderPassInfo = SA::RND::RenderPassInfo<Texture>;
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
