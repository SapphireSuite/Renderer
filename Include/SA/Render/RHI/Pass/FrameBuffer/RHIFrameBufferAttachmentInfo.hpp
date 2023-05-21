// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FRAME_BUFFER_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_FRAME_BUFFER_ATTACHMENT_INFO_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/RHI/Pass/Info/SampleBits.hpp>
#include <SA/Render/RHI/Pass/Info/AttachmentInfo.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkFrameBufferInfo.hpp>

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	struct FrameBufferAttachmentInfo : public AttachmentInfo
	{
		// All attachment from the same subpass must have the same sample count.
		SampleBits sampling = SampleBits::Sample1Bit;

		Vec2ui extents;

		FrameBufferAttachmentInfo() = default;
		FrameBufferAttachmentInfo(const AttachmentInfo& _other) noexcept;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		void API_Vulkan(VK::FrameBufferInfo& _info) const;

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
	};
}

#endif // SAPPHIRE_RENDER_RHI_FRAME_BUFFER_ATTACHMENT_INFO_GUARD
