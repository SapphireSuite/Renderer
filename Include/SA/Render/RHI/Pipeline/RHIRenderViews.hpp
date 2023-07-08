// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_VIEWS_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_VIEWS_GUARD

#include <SA/Maths/Geometry/Rectangle2D.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class RenderViews;
	}

#endif

	namespace RHI
	{
		class CommandBuffer;

		class RenderViews
		{
		public:
			virtual ~RenderViews() = default;

			void AddFullView(Vec2ui _extents);
			virtual void AddView(const Rect2Df& _viewport, const Rect2Dui& _scissor) = 0;

			virtual void Bind(const CommandBuffer* _cmd) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
			virtual const VK::RenderViews& API_Vulkan() const;
#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_VIEWS_GUARD
