// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD

#include "SampleBits.hpp"
#include "SubPassAttachmentDescriptor.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		struct SubPassDescriptor
		{
			// All color attachment must have the same sample count.
			SampleBits sampling = SampleBits::Sample1Bit;

			std::vector<SubPassAttachmentDescriptor> attachmentDescs;
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		void API_AppendRenderSubPassDescriptor(
			const RHI::SubPassDescriptor& _RHIsubpass,
			RenderPassInfo& _vkInfo,
			uint32_t _subpassNum
		);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD
