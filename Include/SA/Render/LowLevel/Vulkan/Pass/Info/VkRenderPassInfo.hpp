// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>
#include <SA/Render/LowLevel/Common/Pass/Info/AttachmentInfoBase.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::VK
{
	struct AttachmentInfo : public AttachmentInfoBase<Texture>
	{
		VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	};

	using SubpassInfo = SA::RND::SubpassInfo<AttachmentInfo>;
	using RenderPassInfo = SA::RND::RenderPassInfo<SubpassInfo>;
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_INFO_GUARD
