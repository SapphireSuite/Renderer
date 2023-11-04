// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIResourceInitializer.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::ResourceInitializer& ResourceInitializer::API_Vulkan()
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::ResourceInitializer& ResourceInitializer::API_DirectX12()
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
