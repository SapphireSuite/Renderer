// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_RENDER_VIEWS_GUARD
#define SAPPHIRE_RENDER_DX12_RENDER_VIEWS_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class CommandList;

	class RenderViews
	{
	public:
		std::vector<D3D12_VIEWPORT> viewports;
		std::vector<D3D12_RECT> scissors;

		void AddView(const D3D12_VIEWPORT& _viewport, const D3D12_RECT& _scissor);
		void AddFullView(Vec2ui _extents);

		void Bind(const CommandList& _cmd);
	};
}

#endif // SAPPHIRE_RENDER_DX12_RENDER_VIEWS_GUARD
