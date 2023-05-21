// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkFrameBuffer.hpp>

#include <Device/VkDevice.hpp>
#include <Pass/VkRenderPass.hpp>

namespace SA::RND::VK
{
	void FrameBuffer::Create(const Device& _device, const FrameBufferInfo& _info)
	{
		SA_ASSERT((Nullptr, _info.pass), SA.Render.Vulkan, L"Valid RenderPass is required to create FrameBuffer")

		Vec2ui fameBufferExtents{INT_MAX, INT_MAX};
		std::vector<VkImageView> views;

		mClearValues = _info.clearValues;
		mAttachments.reserve(_info.imageInfos.size());
		views.reserve(_info.imageInfos.size());

		for(auto& imageInfo : _info.imageInfos)
		{
			auto& imgBuffer = mAttachments.emplace_back();
			imgBuffer.Create(_device, imageInfo);

			views.emplace_back(imgBuffer);

			fameBufferExtents.x = std::min(fameBufferExtents.x, imageInfo.extents.x);
			fameBufferExtents.y = std::min(fameBufferExtents.y, imageInfo.extents.y);
		}


		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = *_info.pass;
		createInfo.attachmentCount = static_cast<uint32_t>(views.size());
		createInfo.pAttachments = views.data();
		createInfo.width = fameBufferExtents.x;
		createInfo.height = fameBufferExtents.y;
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
}
