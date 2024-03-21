// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHID12RenderViews.hpp>

#include <Device/Command/RHID12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	void D12RenderViews::AddView(const Rect2Df& _viewport, const Rect2Dui& _scissor)
	{
		const D3D12_VIEWPORT d12Viewport{
			.TopLeftX = _viewport.x,
			.TopLeftY = _viewport.y,
			.Width = _viewport.width,
			.Height = _viewport.height,
			.MinDepth = 0.0f,
			.MaxDepth = 1.0f,
		};

		const D3D12_RECT d12Scissor{
			.left = static_cast<LONG>(_scissor.x),
			.top = static_cast<LONG>(_scissor.y),
			.right = static_cast<LONG>(_scissor.width),
			.bottom = static_cast<LONG>(_scissor.height),
		};

		mHandle.AddView(d12Viewport, d12Scissor);
	}

	void D12RenderViews::Bind(const CommandBuffer* _cmd)
	{
		mHandle.Bind(_cmd->API_DirectX12());
	}
}
