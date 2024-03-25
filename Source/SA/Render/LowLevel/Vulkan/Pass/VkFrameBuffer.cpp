// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkFrameBuffer.hpp>

#include <Device/VkDevice.hpp>
#include <Pass/VkRenderPass.hpp>

namespace SA::RND::VK
{
	void FrameBuffer::EmplaceImage(const Device& _device, const RenderPassInfo& _info, const AttachmentInfo& _attach, const Texture* _texture)
	{
		const TextureDescriptor& desc = _info.textureToDescriptorMap.at(_texture);

		// TODO: better impl.
		mExtents.x = std::min(mExtents.x, desc.extents.x);
		mExtents.y = std::min(mExtents.y, desc.extents.y);

		VkImageViewCreateInfo info
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.image = *_texture,
			.viewType = VK_IMAGE_VIEW_TYPE_2D, // TODO: set to VK_IMAGE_VIEW_TYPE_CUBE for cubemap.
			.format = desc.format,
			.components = VkComponentMapping{
				.r = VK_COMPONENT_SWIZZLE_IDENTITY,
				.g = VK_COMPONENT_SWIZZLE_IDENTITY,
				.b = VK_COMPONENT_SWIZZLE_IDENTITY,
				.a = VK_COMPONENT_SWIZZLE_IDENTITY,
			},
			.subresourceRange = VkImageSubresourceRange{
				.aspectMask = 0u,
				.baseMipLevel = 0u,
				.levelCount = 1u,
				.baseArrayLayer = 0u,
				.layerCount = 1u, // TODO: set to 6 for cubemap.
			},
		};

		if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_DEPTH_BIT;

			if (_attach.loadOp == VK_ATTACHMENT_LOAD_OP_CLEAR)
			{
				VkClearValue depthClearValue{
					.depthStencil = VkClearDepthStencilValue{
						.depth = desc.clearColor.r,
						.stencil = static_cast<uint32_t>(desc.clearColor.g),
					}
				};
				mClearValues.push_back(depthClearValue);
			}
		}
		else
		{
			info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_COLOR_BIT;

			if (_attach.loadOp == VK_ATTACHMENT_LOAD_OP_CLEAR)
				mClearValues.push_back(desc.clearColor);
		}

		auto& imageView = mImageViews.emplace_back();

		SA_VK_API(vkCreateImageView(_device, &info, nullptr, &imageView), L"Failed to create image view!");
		SA_LOG(L"Image View created.", Info, SA.Render.Vulkan, (L"Handle [%1]", imageView));
	}

	void FrameBuffer::Create(const Device& _device,
		const RenderPass& _pass,
		const RenderPassInfo& _info)
	{
		mExtents = Vec2ui{ INT_MAX, INT_MAX };

		mImageViews.reserve(_info.subpasses.size() * 8);

		for (auto& subpass : _info.subpasses)
		{
			for (auto& attach : subpass.attachments)
			{
				EmplaceImage(_device, _info, attach, attach.texture);

				if (attach.resolved)
					EmplaceImage(_device, _info, attach, attach.resolved);
			}
		}

		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = _pass;
		createInfo.attachmentCount = static_cast<uint32_t>(mImageViews.size());
		createInfo.pAttachments = mImageViews.data();
		createInfo.width = mExtents.x;
		createInfo.height = mExtents.y;
		createInfo.layers = 1;


		SA_VK_API(vkCreateFramebuffer(_device, &createInfo, nullptr, &mHandle), L"Failed to create framebuffer!");

		SA_LOG("FrameBuffer created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle))
	}

	void FrameBuffer::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyFramebuffer(_device, mHandle, nullptr));

		for (auto& view : mImageViews)
		{
			SA_VK_API(vkDestroyImageView(_device, view, nullptr));

			SA_LOG(L"Image View destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", view));
		}

		mImageViews.clear();

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

	FrameBuffer::operator VkFramebuffer() const noexcept
	{
		return mHandle;
	}
}
