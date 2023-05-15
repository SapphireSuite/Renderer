// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/PassDescriptor.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::RenderPassInfo PassDescriptor::API_Vulkan() const
	{
		VK::RenderPassInfo info;

		const uint32_t subpassNum = static_cast<uint32_t>(subpassDescs.size());

		info.subpassDescriptions.reserve(subpassNum);
		info.subpassDependencies.reserve(subpassNum);
		
		info.subpassAttachments.reserve(subpassNum * 8u); // Max 8 attachments by subpass.
		info.subpassDepthAttachmentRefs.reserve(subpassNum);
		info.subpassColorAttachmentRefs.reserve(subpassNum);
		info.subpassAttachmentResolveRefs.reserve(subpassNum);
		info.subpassInputAttachmentRefs.reserve(subpassNum);

		for(const auto& subpassDesc : subpassDescs)
			subpassDesc.API_Vulkan(info, subpassNum);

		return info;
	}

#endif
}
