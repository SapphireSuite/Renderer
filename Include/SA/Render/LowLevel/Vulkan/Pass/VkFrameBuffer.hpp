// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD

#include <SA/Render/LowLevel/Vulkan/Buffers/VkImageBuffer.hpp>

#include "VkFrameBufferInfo.hpp"

namespace SA::RND::VK
{
	class Device;

	class FrameBuffer
	{
		VkFramebuffer mHandle = VK_NULL_HANDLE;

		std::vector<ImageBuffer> mAttachments;
		std::vector<VkClearValue> mClearValues;

	public:
		void Create(const Device& _device, const FrameBufferInfo& _info);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
