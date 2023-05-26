// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

#include <string>
#include <vector> // Used by all children.

namespace SA::RND
{
	struct PassInfoBase
	{
		std::string name;
	};
}

#endif // SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
