// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Texture/TextureUsage.hpp>

namespace SA::RND::DX12
{
	D3D12_RESOURCE_FLAGS API_GetTextureUsage(uint8_t _usage)
	{
		D3D12_RESOURCE_FLAGS usage;

		if (_usage & TextureUsage::RenderTarget)
			usage = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		if (_usage & TextureUsage::Depth)
			usage |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		if (_usage & TextureUsage::UAV)
			usage |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

		return usage;
	}
}
