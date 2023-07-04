// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_PIPELINE_VIEW_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_PIPELINE_VIEW_INFO_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct GraphicsPipelineViewInfo
	{
		std::vector<D3D12_VIEWPORT> viewports;
		std::vector<D3D12_RECT> scissors;

		inline void AddFullViewport(Vec2ui _extents)
		{
			viewports.emplace_back(D3D12_VIEWPORT{
				.TopLeftX = 0.0f,
				.TopLeftY = 0.0f,
				.Width = float(_extents.x),
				.Height = float(_extents.y),
			});

			scissors.emplace_back(D3D12_RECT{
				.left = 0,
				.top = 0,
				.right = static_cast<LONG>(_extents.x),
				.bottom = static_cast<LONG>(_extents.y)
			});
		}
	};
}

#endif // SAPPHIRE_RENDER_DX12_PIPELINE_VIEW_INFO_GUARD
