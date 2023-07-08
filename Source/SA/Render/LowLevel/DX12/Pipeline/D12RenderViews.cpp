// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/D12RenderViews.hpp>

#include <Device/Command/D12CommandList.hpp>

namespace SA::RND::DX12
{
	void RenderViews::AddView(const D3D12_VIEWPORT& _viewport, const D3D12_RECT& _scissor)
	{
		viewports.emplace_back(_viewport);
		scissors.emplace_back(_scissor);
	}

	void RenderViews::AddFullView(Vec2ui _extents)
	{
		viewports.emplace_back(D3D12_VIEWPORT{
			.TopLeftX = 0,
			.TopLeftY = 0,
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

	void RenderViews::Bind(const CommandList& _cmd)
	{
		SA_DX12_API(_cmd->RSSetViewports(static_cast<UINT>(viewports.size()), viewports.data()));
		SA_DX12_API(_cmd->RSSetScissorRects(static_cast<UINT>(scissors.size()), scissors.data()));
	}
}
