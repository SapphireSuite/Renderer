// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/PassInfoBase.hpp>

#include "VkSubpassInfo.hpp"

namespace SA::RND::VK
{
	struct PassInfo : public PassInfoBase
	{
		std::vector<SubpassInfo> subpasses;
	};
}

#endif // SAPPHIRE_RENDER_VK_PASS_INFO_GUARD
