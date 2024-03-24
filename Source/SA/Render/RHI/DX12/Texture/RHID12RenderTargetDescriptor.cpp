// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Texture/RHIRenderTargetDescriptor.hpp>

namespace SA::RND::RHI
{
	DX12::TextureDescriptor RenderTargetDescriptor::API_DirectX12() const noexcept
	{
		return DX12::TextureDescriptor{
			.extents = extents,
			.format = DX12::API_GetFormat(format),
			.sampling = DX12::API_GetSampling(sampling),
			.usage = DX12::API_GetTextureUsage(usage),
			.clearColor = clearColor,
		};
	}

}