// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SUBPASS_INFO_GUARD
#define SAPPHIRE_RENDER_VK_SUBPASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/SubpassInfoBase.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include "VkAttachmentInfo.hpp"

namespace SA::RND::VK
{
	struct SubpassInfo : public SubpassInfoBase
	{
		// All color attachments must have the same sample count.
		VkSampleCountFlagBits sampling = VK_SAMPLE_COUNT_1_BIT;

		std::vector<AttachmentInfo> attachments;
	};
}

#endif // SAPPHIRE_RENDER_VK_SUBPASS_INFO_GUARD
