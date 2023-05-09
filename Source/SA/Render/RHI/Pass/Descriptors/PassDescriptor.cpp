// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/PassDescriptor.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		RenderPassInfo API_MakeRenderPassDescriptor(const RHI::PassDescriptor& _RHIpass)
		{
			RenderPassInfo info;

			const uint32_t subpassNum = static_cast<uint32_t>(_RHIpass.subPassDescs.size());

			info.subpassDescriptions.reserve(subpassNum);
			info.subpassDependencies.reserve(subpassNum);
			
			info.subpassAttachments.reserve(subpassNum * 8u); // Max 8 attachments by subpass.
			info.subpassDepthAttachmentRefs.reserve(subpassNum);
			info.subpassColorAttachmentRefs.reserve(subpassNum);
			info.subpassAttachmentResolveRefs.reserve(subpassNum);
			info.subpassInputAttachmentRefs.reserve(subpassNum);

			for(const auto& RHIsubpass : _RHIpass.subPassDescs)
			{
				API_AppendRenderSubPassDescriptor(RHIsubpass, info, subpassNum);
			}

			return info;
		}
	}

#endif
}
