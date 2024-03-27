// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_RENDER_VIEWS_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_RENDER_VIEWS_GUARD

#include <SA/Render/RHI/Common/Pipeline/RHIRenderViews.hpp>

#include <SA/Render/LowLevel/DX12/Pipeline/D12RenderViews.hpp>

namespace SA::RND::RHI
{
	class D12RenderViews : public RenderViews
	{
		DX12::RenderViews mHandle;

	public:
		void AddView(const Rect2Df& _viewport, const Rect2Dui& _scissor) override final;

		void Bind(const CommandBuffer* _cmd) override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_RENDER_VIEWS_GUARD
