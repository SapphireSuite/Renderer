// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIGraphicsPipelineViewInfo.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
#include <SA/Render/LowLevel/Vulkan/Pipeline/Info/VkGraphicsPipelineViewInfo.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
#include <SA/Render/LowLevel/DX12/Pipeline/Info/D12GraphicsPipelineViewInfo.hpp>
#endif

namespace SA::RND::RHI
{
	void GraphicsPipelineViewInfo::AddFullViewport(Vec2ui _extents)
	{
		viewports.emplace_back(Rect2Df{ Vec2f::Zero, _extents });
		scissors.emplace_back(Rect2Dui{ Vec2ui::Zero, _extents });
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::GraphicsPipelineViewInfo GraphicsPipelineViewInfo::API_Vulkan() const
	{
		VK::GraphicsPipelineViewInfo vkViews;

		for (auto& vp : viewports)
		{
			VkViewport& vkVP = vkViews.viewports.emplace_back();

			// Invert Viewport to flip Y-axis.
			vkVP.x = vp.x;
			vkVP.y = vp.height;
			vkVP.width = vp.width;
			vkVP.height = -vp.height;
		}

		for (auto& scissor : scissors)
		{
			VkRect2D& vkScissor = vkViews.scissors.emplace_back();

			vkScissor.offset.x = scissor.x;
			vkScissor.offset.y = scissor.y;
			vkScissor.extent.width = scissor.width;
			vkScissor.extent.height = scissor.height;
		}

		return vkViews;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::GraphicsPipelineViewInfo GraphicsPipelineViewInfo::API_DirectX12() const
	{
		DX12::GraphicsPipelineViewInfo d12Views;

		for (auto& vp : viewports)
		{
			D3D12_VIEWPORT& vkVP = d12Views.viewports.emplace_back();

			vkVP.TopLeftX = vp.x;
			vkVP.TopLeftY = vp.y;
			vkVP.Width = vp.width;
			vkVP.Height = vp.height;
		}

		for (auto& scissor : scissors)
		{
			D3D12_RECT& vkScissor = d12Views.scissors.emplace_back();

			vkScissor.left = scissor.x;
			vkScissor.top = scissor.y;
			vkScissor.right = scissor.width;
			vkScissor.bottom = scissor.height;
		}

		return d12Views;
	}

#endif
}
