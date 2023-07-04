// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_VIEW_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_VIEW_INFO_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Geometry/Rectangle2D.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		struct GraphicsPipelineViewInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		struct GraphicsPipelineViewInfo;
	}

#endif

	namespace RHI
	{
		struct GraphicsPipelineViewInfo
		{
			std::vector<Rect2Df> viewports;
			std::vector<Rect2Dui> scissors;

			void AddFullViewport(Vec2ui _extents);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			VK::GraphicsPipelineViewInfo API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			DX12::GraphicsPipelineViewInfo API_DirectX12() const;
#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_GRAPHICS_PIPELINE_VIEW_INFO_GUARD
