// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_VK_PASS_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include "RHIPass.hpp"

#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>

namespace SA::RND::RHI
{
	class VkPass : public Pass
	{
		VK::RenderPass mHandle;

	public:
		const VK::RenderPass* API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_PASS_GUARD
