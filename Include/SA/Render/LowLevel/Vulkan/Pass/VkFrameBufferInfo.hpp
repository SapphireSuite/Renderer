// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPHIRE_RENDER_VK_FRAMEBUFFER_INFO_GUARD
#define SAPHIRE_RENDER_VK_FRAMEBUFFER_INFO_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>
#include <SA/Render/LowLevel/Vulkan/Buffers/VkImageBufferInfo.hpp>

namespace SA::RND::VK
{
	class RenderPass;

	struct FrameBufferInfo
	{
		const RenderPass* pass = nullptr;

		std::vector<ImageBufferInfo> imageInfos;
		std::vector<VkClearValue> clearValues;

		void SetAllAttachmentsExtents(const Vec2ui& _extents);
	};
}

#endif // SAPHIRE_RENDER_VK_FRAMEBUFFER_INFO_GUARD
