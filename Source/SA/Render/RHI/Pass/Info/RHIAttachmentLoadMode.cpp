// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHIAttachmentLoadMode.hpp>

#include <SA/Collections/Debug>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkAttachmentLoadOp API_GetAttachmentLoadOp(RHI::AttachmentLoadMode _mode)
		{
			static constexpr VkAttachmentLoadOp vkAttachLoadOpIndexMap[] = {
				VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				VK_ATTACHMENT_LOAD_OP_LOAD,
				VK_ATTACHMENT_LOAD_OP_CLEAR
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkAttachLoadOpIndexMap)), SA.Render.RHI.Vulkan,
				(L"RenderTargetLoadMode value [%1] invalid", index));

			return vkAttachLoadOpIndexMap[index];
		}
	}

#endif
}