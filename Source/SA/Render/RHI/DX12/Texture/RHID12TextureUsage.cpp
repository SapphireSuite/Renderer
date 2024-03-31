// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Texture/RHITextureUsage.hpp>

namespace SA::RND::DX12
{
	D3D12_RESOURCE_FLAGS API_GetTextureUsage(RHI::TextureUsage _usage)
	{
		D3D12_RESOURCE_FLAGS d12Flags = D3D12_RESOURCE_FLAG_NONE;

		// TODO: Warning check only one of Color and Depth is set.

		if (_usage & RHI::TextureUsageFlags::Color)
			d12Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		if (_usage & RHI::TextureUsageFlags::Depth)
			d12Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		return d12Flags;
	}
}
