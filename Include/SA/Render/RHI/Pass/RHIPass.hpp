// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>

#endif

namespace SA::RND::RHI
{
	class Pass
	{
	public:

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		virtual const VK::RenderPass* API_Vulkan() const;
#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_PASS_GUARD
