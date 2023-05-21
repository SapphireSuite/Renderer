// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/FrameBuffer/RHIFrameBufferInfo.hpp>

#include <Pass/Info/PassInfo.hpp>

namespace SA::RND::RHI
{
	void FrameBufferInfo::InitFromPass(const Pass* _pass, const PassInfo& _info)
	{
		pass = _pass;

		attachments.clear();
		attachments.reserve(_info.subpasses.size() * 8);

		for(auto& subpass : _info.subpasses)
		{
			// Add FrameBuffer attachment for each render target.
			for(auto& RT : subpass.RTs)
			{
				FrameBufferAttachmentInfo& attach = attachments.emplace_back(RT);
				attach.sampling = subpass.sampling;
			}
		}
	}

	void FrameBufferInfo::SetAllAttachmentsExtents(const Vec2ui& _extents)
	{
		for(auto& attach : attachments)
			attach.extents = _extents;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::FrameBufferInfo FrameBufferInfo::API_Vulkan() const
	{
		VK::FrameBufferInfo info;

		info.imageInfos.reserve(attachments.size());
		info.clearValues.reserve(attachments.size());

		for(auto& attach : attachments)
		{
			attach.API_Vulkan(info);
			// info.imageInfos.emplace_back(attach.API_Vulkan());
		}

		return info;
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
}
