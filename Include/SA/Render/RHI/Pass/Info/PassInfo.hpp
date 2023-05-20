// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD

#include "SubpassInfo.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND::RHI
{
	struct PassInfo
	{
		std::vector<SubpassInfo> subpasses;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::RenderPassInfo API_Vulkan() const;
		
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PASS_INFO_GUARD
