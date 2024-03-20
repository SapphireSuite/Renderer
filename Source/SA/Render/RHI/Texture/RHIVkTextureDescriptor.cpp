// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Texture/RHITextureDescriptor.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::TextureDescriptor TextureDescriptor::API_Vulkan() const noexcept
	{
		return VK::TextureDescriptor{
			.extents = extents,
			.mipLevels = mipLevels,
			.format = VK::API_GetFormat(format),
			.sampling = VK::API_GetSampling(sampling),
			.usage = VK::API_GetTextureUsage(usage),
			.bPresentAttachment = (usage & TextureUsage::Present) != 0u
		};
	}

#endif
}
