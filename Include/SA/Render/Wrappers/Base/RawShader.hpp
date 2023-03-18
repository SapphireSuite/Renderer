// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_BASE_RAW_SHADER_GUARD
#define SAPPHIRE_RENDER_BASE_RAW_SHADER_GUARD

#include <cstdint>
#include <vector>

namespace SA
{
	struct RawShader
	{
		std::vector<uint32_t> data;

		void Clear();
	};
}

#endif // SAPPHIRE_RENDER_BASE_RAW_SHADER_GUARD
