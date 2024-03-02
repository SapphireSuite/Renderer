// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RAW_TEXTURE_GUARD
#define SAPPHIRE_RENDER_COMMON_RAW_TEXTURE_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Format.hpp>

namespace SA::RND
{
	struct RawTexture
	{
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		Format format = Format::R8G8B8A8_UNORM;

		std::vector<char> data;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RAW_TEXTURE_GUARD
