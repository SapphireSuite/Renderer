// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Texture/TextureUsage.hpp>

namespace SA::RND::DX12
{
	D3D12_RESOURCE_FLAGS API_GetTextureUsage(uint8_t _usage)
	{
		D3D12_RESOURCE_FLAGS d12Flags;

		if (_usage & TextureUsage::RenderTarget)
			d12Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		if (_usage & TextureUsage::Depth)
			d12Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		if (_usage & TextureUsage::UAV)
			d12Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

		return d12Flags;
	}

	uint8_t API_GetTextureUsage(D3D12_RESOURCE_FLAGS _d12Flags)
	{
		uint8_t usage = 0u;

		if (_d12Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
			usage |= TextureUsage::RenderTarget;

		if (_d12Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
			usage |= TextureUsage::Depth;

		if (_d12Flags & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)
			usage |= TextureUsage::UAV;

		return usage;
	}
}
