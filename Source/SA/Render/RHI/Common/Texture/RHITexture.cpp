// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHITexture.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::Texture& Texture::API_Vulkan()
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

	const VK::Texture& Texture::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::Texture& Texture::API_DirectX12()
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

	const DX12::Texture& Texture::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
