// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_VK_ATTACHMENT_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/AttachmentInfoBase.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	struct AttachmentInfo : public AttachmentInfoBase
	{
		VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
		VkAttachmentLoadOp loadMode = VK_ATTACHMENT_LOAD_OP_CLEAR;
	};
}

#endif // SAPPHIRE_RENDER_VK_ATTACHMENT_INFO_GUARD
