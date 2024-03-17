// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Pass/Info/AttachmentLoadMode.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::VK
{
	VkAttachmentLoadOp API_GetAttachmentLoadOp(AttachmentLoadMode _mode)
	{
		static constexpr VkAttachmentLoadOp vkAttachLoadOpIndexMap[] = {
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_LOAD_OP_LOAD,
			VK_ATTACHMENT_LOAD_OP_CLEAR
		};

		const uint8_t index = static_cast<uint8_t>(_mode);

		SA_ASSERT((OutOfRange, index, 0u, sizeof(vkAttachLoadOpIndexMap)), SA.Render.Vulkan,
			(L"AttachmentLoadMode value [%1] invalid", index));

		return vkAttachLoadOpIndexMap[index];
	}
}
