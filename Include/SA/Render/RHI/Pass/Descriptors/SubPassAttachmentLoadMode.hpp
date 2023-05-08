// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_LOAD_MODE_GUARD
#define SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_LOAD_MODE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class SubPassAttachmentLoadMode : uint8_t
		{
			None,

			Load,

			Clear,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkAttachmentLoadOp API_GetAttachmentLoadOp(const RHI::SubPassAttachmentLoadMode _mode) noexcept;
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_LOAD_MODE_GUARD
