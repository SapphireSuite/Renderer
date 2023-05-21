// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/FrameBuffer/RHIFrameBufferAttachmentInfo.hpp>

namespace SA::RND::RHI
{
	FrameBufferAttachmentInfo::FrameBufferAttachmentInfo(const AttachmentInfo& _other) noexcept :
		AttachmentInfo(_other)
	{
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	void FrameBufferAttachmentInfo::API_Vulkan(VK::FrameBufferInfo& _info) const
	{
		VK::ImageBufferInfo imgInfo;

		imgInfo.format = VK::API_GetFormat(format);
		imgInfo.extents = extents;

		imgInfo.sampling = VK::API_GetSampleCount(sampling);

		if(type == AttachmentType::Color)
		{
			imgInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			imgInfo.aspectFlags |= VK_IMAGE_ASPECT_COLOR_BIT;

			if(imgInfo.sampling > VK_SAMPLE_COUNT_1_BIT)
			{
				// Add multisampled image
				/* VK::ImageBufferInfo& multSampledInfo = */_info.imageInfos.emplace_back(imgInfo);

				if(loadMode == AttachmentLoadMode::Clear) // multisampled clear color.
					_info.clearValues.push_back(clearColor);

				// reset current to single sampling for resolution.
				imgInfo.sampling = VK_SAMPLE_COUNT_1_BIT;
			}

			if(loadMode == AttachmentLoadMode::Clear)
				_info.clearValues.push_back(clearColor);
		}
		else if(type == AttachmentType::Depth)
		{
			imgInfo.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			imgInfo.aspectFlags |= VK_IMAGE_ASPECT_DEPTH_BIT;

			if(loadMode == AttachmentLoadMode::Clear)
				_info.clearValues.push_back(VkClearValue{ { 1.0f, 0u } }); // TODO: Color IMPL
		}

		if(usage == AttachmentUsage::InputNext)
			imgInfo.usage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		_info.imageInfos.emplace_back(imgInfo);
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
}
