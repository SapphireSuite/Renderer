// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIFrameBuffer.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::FrameBuffer& FrameBuffer::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::FrameBuffer& FrameBuffer::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.Vulkan);
	}

#endif
}
