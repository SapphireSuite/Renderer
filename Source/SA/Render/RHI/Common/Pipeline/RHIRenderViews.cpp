// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIRenderViews.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	void RenderViews::AddFullView(Vec2ui _extents)
	{
		Rect2Df viewport;
		viewport.x = 0;
		viewport.y = 0;
		viewport.width = float(_extents.x);
		viewport.height = float(_extents.y);

		Rect2Dui scissor;
		scissor.offset = Vec2ui::Zero;
		scissor.extent = _extents;


		AddView(viewport, scissor);
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::RenderViews& RenderViews::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif
}
