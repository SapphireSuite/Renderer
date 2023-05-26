// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

#include <string>
#include <vector>

namespace SA::RND
{
	template <typename SubpassT>
	struct PassInfoBase
	{
		std::string name;

		std::vector<SubpassT> subpasses;

	};
}

#endif // SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
