// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDE_RHI_RENDER_TARGET_INFO_GUARD
#define SAPPHIRE_RENDE_RHI_RENDER_TARGET_INFO_GUARD

#include "AttachmentInfo.hpp"

namespace SA::RND::RHI
{
	struct RenderTargetInfo : public AttachmentInfo
	{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		// Append descriptor to VkInfo.
		void API_Vulkan(
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			std::vector<VkAttachmentReference>& _colorAttachmentRefs,
			VkAttachmentReference& _depthAttachRef,
			std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		) const;

#endif
	};
}

#endif // SAPPHIRE_RENDE_RHI_RENDER_TARGET_INFO_GUARD
