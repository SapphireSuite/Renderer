// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/SubPassDescriptor.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		namespace Intl
		{
			VkSubpassDescription CreateSubpassDesc()
			{
				VkSubpassDescription subpass{};

				subpass.flags = 0u;
				subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

				subpass.inputAttachmentCount = 0u;
				subpass.pInputAttachments = nullptr;

				subpass.colorAttachmentCount = 0u;
				subpass.pColorAttachments = nullptr;
				subpass.pResolveAttachments = nullptr;

				subpass.pDepthStencilAttachment = nullptr;

				subpass.preserveAttachmentCount = 0u;
				subpass.pPreserveAttachments = nullptr;

				return subpass;
			}

			VkSubpassDependency CreateSubpassDep(uint32_t _currIndex, uint32_t _subpassNum)
			{
				VkSubpassDependency subpassDependency{};

				// Default dependency.
				subpassDependency.srcSubpass = _currIndex - 1;
				subpassDependency.dstSubpass = _currIndex;

				subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

				subpassDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

				subpassDependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

				// Specialization: first dependency.
				if (_currIndex == 0)
				{
					subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;

					subpassDependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

					subpassDependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
				}

				// Specialization: last dependency.
				if (_currIndex == _subpassNum - 1)
				{
					subpassDependency.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

					subpassDependency.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
				}

				return subpassDependency;
			}
		}

		void API_AppendRenderSubPassDescriptor(
			const RHI::SubPassDescriptor& _RHIsubpass,
			RenderPassInfo& _vkInfo,
			uint32_t _subpassNum
		)
		{
			const VkSampleCountFlagBits sampling = API_GetSampleCount(_RHIsubpass.sampling);

			VkAttachmentReference& depthAttachRef = _vkInfo.subpassDepthAttachmentRefs.emplace_back(
				VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
		
			const uint32_t attachmentNum = static_cast<uint32_t>(_RHIsubpass.attachmentDescs.size());

			std::vector<VkAttachmentReference>& colorAttachmentRefs = _vkInfo.subpassColorAttachmentRefs.emplace_back();
			colorAttachmentRefs.reserve(attachmentNum);

			std::vector<VkAttachmentReference>& resolveAttachmentRefs = _vkInfo.subpassAttachmentResolveRefs.emplace_back();
			resolveAttachmentRefs.reserve(attachmentNum);

			std::vector<VkAttachmentReference>& inputAttachmentRefs = _vkInfo.subpassInputAttachmentRefs.emplace_back();
			inputAttachmentRefs.reserve(attachmentNum);

			for(const auto& attachmentDesc : _RHIsubpass.attachmentDescs)
			{
				API_AppendRenderSubPassAttachmentDescriptor(
					attachmentDesc,
					sampling,
					_vkInfo.subpassAttachments,
					depthAttachRef,
					colorAttachmentRefs,
					resolveAttachmentRefs,
					inputAttachmentRefs
				);
			}

			const uint32_t subpassIndex = static_cast<uint32_t>(_vkInfo.subpassDescriptions.size());
			VkSubpassDescription& vkSubpassDesc = _vkInfo.subpassDescriptions.emplace_back(Intl::CreateSubpassDesc());

			vkSubpassDesc.pDepthStencilAttachment = &depthAttachRef;
			vkSubpassDesc.colorAttachmentCount = static_cast<uint32_t>(colorAttachmentRefs.size());
			vkSubpassDesc.pColorAttachments = colorAttachmentRefs.data();
			vkSubpassDesc.pResolveAttachments = resolveAttachmentRefs.data();

			if (subpassIndex > 0)
			{
				// Add input attachment from previous subpass.
				vkSubpassDesc.inputAttachmentCount = static_cast<uint32_t>(_vkInfo.subpassInputAttachmentRefs[subpassIndex - 1].size());
				vkSubpassDesc.pInputAttachments = _vkInfo.subpassInputAttachmentRefs[subpassIndex - 1].data();
			}

			// Subpass dependency.
			/*VkSubpassDependency& subpassDep =*/ _vkInfo.subpassDependencies.emplace_back(Intl::CreateSubpassDep(subpassIndex, _subpassNum));
		}
	}

#endif
}
