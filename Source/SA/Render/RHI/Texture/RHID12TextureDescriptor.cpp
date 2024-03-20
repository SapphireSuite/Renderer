// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Texture/RHITextureDescriptor.hpp>

namespace SA::RND::RHI
{
	DX12::TextureDescriptor TextureDescriptor::API_DirectX12() const noexcept
	{
		return DX12::TextureDescriptor{
			.extents = extents,
			.mipLevels = mipLevels,
			.format = DX12::API_GetFormat(format),
			.sampling = DX12::API_GetSampling(sampling),
			.usage = DX12::API_GetTextureUsage(usage)
		};
	}
}
