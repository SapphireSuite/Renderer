// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIPipeline.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Pipeline& Pipeline::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Pipeline& Pipeline::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
