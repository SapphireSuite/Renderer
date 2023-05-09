// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Misc/Format.hpp>

#include "SubPassAttachmentLoadMode.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		struct SubPassAttachmentDescriptor
		{
			Format format = Format::R8G8B8A8_UNORM;

			// Used as input attachment in next subpass.
			bool bInputNext = false;

			SubPassAttachmentLoadMode loadMode = SubPassAttachmentLoadMode::Clear;
			
			Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		void API_AppendRenderSubPassAttachmentDescriptor(
			const RHI::SubPassAttachmentDescriptor& _RHIsubpassAttach,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			VkAttachmentReference& _depthAttachRef,
			std::vector<VkAttachmentReference>& _colorAttachmentRefs,
			std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD
