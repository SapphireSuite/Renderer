// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD

#include "VkRenderPassInfo.hpp"

namespace SA::RND::VK
{
	class Device;
	class RenderPass;

	class FrameBuffer
	{
		VkFramebuffer mHandle = VK_NULL_HANDLE;

		std::vector<VkImageView> mImageViews;
		std::vector<VkClearValue> mClearValues;

		Vec2ui mExtents;

		void EmplaceImage(const Device& _device, const AttachmentInfo<Texture>& _attach, Texture* _texture);

	public:
		void Create(const Device& _device,
			const RenderPass& _pass,
			const RenderPassInfo& _info);
		void Destroy(const Device& _device);

		const Vec2ui& GetExtents() const;
		const std::vector<VkClearValue>& GetClearValues() const;

		VkImageView GetImageView(uint32_t _index);

		operator VkFramebuffer() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
