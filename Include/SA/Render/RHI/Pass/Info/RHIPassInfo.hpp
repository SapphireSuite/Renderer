// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/PassInfoBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkPassInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/Pass/Info/D12PassInfo.hpp>

#endif

#include "RHISubpassInfo.hpp"

namespace SA::RND::RHI
{
	struct PassInfo : public PassInfoBase<SubpassInfo>
	{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::PassInfo API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::PassInfo API_DirectX12() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD
