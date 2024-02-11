// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfoBase.hpp>

#include "VkSubpassInfo.hpp"

namespace SA::RND::VK
{
	struct RenderPassInfo : public RenderPassInfoBase<SubpassInfo>
	{
	};
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
