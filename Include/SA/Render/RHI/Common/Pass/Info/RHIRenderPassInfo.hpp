// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RHI_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RHI_RENDER_PASS_INFO_GUARD

#include "RHISubpassInfo.hpp"

namespace SA::RND::RHI
{
	struct RenderPassInfo
	{
		std::string name;

		std::vector<SubpassInfo> subpasses;

		SubpassInfo& AddSubpass(std::string _name);
		bool RemoveSubpass(std::string_view _name);
	};
}

#endif // SAPPHIRE_RHI_RENDER_PASS_INFO_GUARD
