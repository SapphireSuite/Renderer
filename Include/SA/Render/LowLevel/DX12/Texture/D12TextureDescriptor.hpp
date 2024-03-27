// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_TEXTURE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_DX12_TEXTURE_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct TextureDescriptor
	{
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		uint32_t sampling = 1u;

		D3D12_RESOURCE_FLAGS usage = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		Color clearColor = Color::black;
	};
}

#endif // SAPPHIRE_RENDER_DX12_TEXTURE_DESCRIPTOR_GUARD
