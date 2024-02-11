// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfoBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkRenderPassInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/Pass/Info/D12RenderPassInfo.hpp>

#endif

#include "RHISubpassInfo.hpp"

namespace SA::RND::RHI
{
	struct RenderPassInfo : public RenderPassInfoBase<SubpassInfo>
	{
		void SetAllSubpassesSampling(Sampling _sampling);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::RenderPassInfo API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::RenderPassInfo API_DirectX12() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
