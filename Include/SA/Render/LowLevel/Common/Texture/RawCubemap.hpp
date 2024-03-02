// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RAW_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_COMMON_RAW_CUBEMAP_GUARD

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

namespace SA::RND
{
	struct RawCubemap
	{
		RawTexture texture;
		RawTexture irradiance;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RAW_CUBEMAP_GUARD
