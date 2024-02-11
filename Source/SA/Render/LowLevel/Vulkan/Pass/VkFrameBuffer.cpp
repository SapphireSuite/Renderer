// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkFrameBuffer.hpp>

#include <Device/VkDevice.hpp>
#include <Pass/VkRenderPass.hpp>

namespace SA::RND::VK
{
	void FrameBuffer::Create(const Device& _device,
			const RenderPass& _pass,
			const RenderPassInfo& _info,
			VkImage _presentImage)
	{
		mExtents = Vec2ui{INT_MAX, INT_MAX};

		for(auto& subpass : _info.subpasses)
		{
			for(auto& attach : subpass.attachments)
			{
				VK::ImageBufferInfo imgInfo;

				imgInfo.sampling = subpass.sampling;

				imgInfo.format = attach.format;
				imgInfo.extents = attach.extents;

				mExtents.x = std::min(mExtents.x, attach.extents.x);
				mExtents.y = std::min(mExtents.y, attach.extents.y);

				if(attach.type == AttachmentType::Color)
				{
					imgInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
					imgInfo.aspectFlags |= VK_IMAGE_ASPECT_COLOR_BIT;

					if(imgInfo.sampling > VK_SAMPLE_COUNT_1_BIT)
					{
						// Add multisampled image
						ImageBuffer& multSampledImg = mAttachments.emplace_back();
						multSampledImg.Create(_device, imgInfo);

						if(attach.loadMode == VK_ATTACHMENT_LOAD_OP_CLEAR) // multisampled clear color.
							mClearValues.push_back(attach.clearColor);

						// reset current to single sampling for resolution.
						imgInfo.sampling = VK_SAMPLE_COUNT_1_BIT;
					}

					if(attach.loadMode == VK_ATTACHMENT_LOAD_OP_CLEAR)
						mClearValues.push_back(attach.clearColor);
				}
				else if(attach.type == AttachmentType::Depth)
				{
					imgInfo.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
					imgInfo.aspectFlags |= VK_IMAGE_ASPECT_DEPTH_BIT;

					if(attach.loadMode == VK_ATTACHMENT_LOAD_OP_CLEAR)
						mClearValues.push_back(VkClearValue{ { { attach.clearColor.r, attach.clearColor.g } } });
				}


				ImageBuffer& imgBuffer = mAttachments.emplace_back();

				if(attach.usage == AttachmentUsage::Present)
				{
					SA_ASSERT((Default, _presentImage != VK_NULL_HANDLE), SA.Render.Vulkan,
						L"Input present image handle must be valid with AttachmentUsage::Present");

					imgBuffer.CreateFromImage(_device, _presentImage, imgInfo);
				}
				else
				{
					if(attach.usage == AttachmentUsage::InputNext)
						imgInfo.usage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

					imgBuffer.Create(_device, imgInfo);
				}
			}
		}
	

		// Image views only required.
		std::vector<VkImageView> views;
		views.reserve(mAttachments.size());

		for(const auto& imgBuffer : mAttachments)
			views.emplace_back(imgBuffer);
		//

		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = _pass;
		createInfo.attachmentCount = static_cast<uint32_t>(views.size());
		createInfo.pAttachments = views.data();
		createInfo.width = mExtents.x;
		createInfo.height = mExtents.y;
		createInfo.layers = 1;


		SA_VK_API(vkCreateFramebuffer(_device, &createInfo, nullptr, &mHandle), L"Failed to create framebuffer!");
	
		SA_LOG("FrameBuffer created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle))
	}
	
	void FrameBuffer::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyFramebuffer(_device, mHandle, nullptr));
		
		for(auto& attach : mAttachments)
			attach.Destroy(_device);

		mAttachments.clear();
		mClearValues.clear();

		SA_LOG("FrameBuffer destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		mHandle = VK_NULL_HANDLE;
	}


	const Vec2ui& FrameBuffer::GetExtents() const
	{
		return mExtents;
	}

	const std::vector<VkClearValue>& FrameBuffer::GetClearValues() const
	{
		return mClearValues;
	}

	const ImageBuffer& FrameBuffer::GetAttachment(uint32_t _index) const
	{
		SA_ASSERT((OutOfArrayRange, _index, mAttachments), SA.Render.Vulkan, L"Attachment index out of framebuffer attachments range");

		return mAttachments[_index];
	}

	FrameBuffer::operator VkFramebuffer() const noexcept
	{
		return mHandle;
	}
}
