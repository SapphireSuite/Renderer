// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD

#include "SubPassDescriptor.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		struct PassDescriptor
		{
			std::vector<SubPassDescriptor> subPassDescs;
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		RenderPassInfo API_MakeRenderPassDescriptor(const RHI::PassDescriptor& _RHIpass);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD
