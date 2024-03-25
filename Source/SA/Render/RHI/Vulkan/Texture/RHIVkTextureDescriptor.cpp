// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Texture/RHITextureDescriptor.hpp>

namespace SA::RND::RHI
{
	VK::TextureDescriptor TextureDescriptor::API_Vulkan() const
	{
		return VK::TextureDescriptor{
			.extents = extents,
			.format = VK::API_GetFormat(format),
			.sampling = VK::API_GetSampling(sampling),
			.usage = VK::API_GetTextureUsage(usage),
			.clearColor = clearColor,
		};
	}
}
