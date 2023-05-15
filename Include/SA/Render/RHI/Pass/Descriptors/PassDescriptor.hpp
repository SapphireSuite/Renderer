// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD

#include "SubpassDescriptor.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND::RHI
{
	struct PassDescriptor
	{
		std::vector<SubpassDescriptor> subpassDescs;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::RenderPassInfo API_Vulkan() const;
		
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD
