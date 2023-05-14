// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Misc/Format.hpp>

#include "RenderTargetLoadMode.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPassInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		struct RenderTargetDescriptor
		{
			Format format = Format::R8G8B8A8_UNORM;

			Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };
			
			RenderTargetLoadMode loadMode = RenderTargetLoadMode::Clear;

			// Used as input attachment in next subpass.
			bool bInputNext = true;
		};

		struct DepthTargetDescriptor : public RenderTargetDescriptor
		{
			bool bEnabled = false;

			DepthTargetDescriptor();
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		void API_AppendRenderTargetDescriptor(
			const RHI::RenderTargetDescriptor& _RTDesc,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			std::vector<VkAttachmentReference>& _colorAttachmentRefs,
			std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		);

		void API_AppendDepthTargetDescriptor(
			const RHI::DepthTargetDescriptor& _depthDesc,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			VkAttachmentReference& _depthAttachRef,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_TARGET_DESCRIPTOR_GUARD
