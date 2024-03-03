// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Format.hpp>
#include <SA/Render/LowLevel/Common/Misc/Sampling.hpp>

namespace SA::RND
{
	struct TextureDescriptor
	{
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		Format format = Format::R8G8B8A8_UNORM;

		Sampling sampling = Sampling::S1Bit;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD
