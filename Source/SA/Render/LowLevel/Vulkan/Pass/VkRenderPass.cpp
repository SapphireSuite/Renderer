// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkRenderPass.hpp>

#include <Device/VkDevice.hpp>
#include <Device/Command/VkCommandBuffer.hpp>
#include <Pass/VkFrameBuffer.hpp>

namespace SA::RND::VK
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
		
		VkSubpassDependency CreateSubpassDependency(uint32_t _currIndex, uint32_t _subpassNum)
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


		VkAttachmentDescription CreateAttachment(VkFormat _format, VkSampleCountFlagBits _sampling, VkAttachmentLoadOp _loadOp)
		{
			VkAttachmentDescription attachment{};
			attachment.flags = 0u;
			attachment.format = _format;
			attachment.samples = _sampling;
			attachment.loadOp = _loadOp;
			attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.stencilLoadOp = _loadOp;
			attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			attachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			return attachment;
		}
	}

	void RenderPass::Create(const Device& _device, const PassInfo& _info)
	{
		const uint32_t subpassNum = static_cast<uint32_t>(_info.subpasses.size());
		const uint32_t attachmentNum = static_cast<uint32_t>(subpassNum * 8);

		std::vector<VkSubpassDescription> subpassDescriptions;
		subpassDescriptions.reserve(subpassNum);
		std::vector<VkSubpassDependency> subpassDependencies;
		subpassDependencies.reserve(subpassNum);

		std::vector<VkAttachmentDescription> attachmentDescs;
		attachmentDescs.reserve(attachmentNum);
		std::vector<VkAttachmentReference> depthAttachmentRefs;
		depthAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassColorAttachmentRefs;
		subpassColorAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassResolveAttachmentRefs;
		subpassResolveAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassInputAttachmentRefs;
		subpassInputAttachmentRefs.reserve(subpassNum);

		for(auto& subpass : _info.subpasses)
		{
			// Per-Subpass attachment refs.
			std::vector<VkAttachmentReference>& colorAttachmentRefs = subpassColorAttachmentRefs.emplace_back();
			colorAttachmentRefs.reserve(attachmentNum);

			std::vector<VkAttachmentReference>& resolveAttachmentRefs = subpassResolveAttachmentRefs.emplace_back();
			resolveAttachmentRefs.reserve(attachmentNum);
			
			std::vector<VkAttachmentReference>& inputAttachmentRefs = subpassInputAttachmentRefs.emplace_back();
			inputAttachmentRefs.reserve(attachmentNum);

			VkAttachmentReference& depthAttachRef = depthAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
			//

			for(auto& attach: subpass.attachments)
			{
				const uint32_t attachIndex = static_cast<uint32_t>(attachmentDescs.size());
				VkAttachmentDescription& attachDesc =
					attachmentDescs.emplace_back(Intl::CreateAttachment(attach.format,
						subpass.sampling, attach.loadMode));

				if(attach.type == AttachmentType::Color)
				{
					/*VkAttachmentReference& colorAttachRef =*/ colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
					VkAttachmentReference& resolveAttachRef = resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
				
				
					if(subpass.sampling != VK_SAMPLE_COUNT_1_BIT)
					{
						// Color attachment multisampling resolution.

						const uint32_t resolvAttachIndex = static_cast<uint32_t>(attachmentDescs.size());
						VkAttachmentDescription& resolveAttachDesc = attachmentDescs.emplace_back(Intl::CreateAttachment(attach.format, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

						if (attach.usage == AttachmentUsage::Present)
							resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

						resolveAttachRef.attachment = resolvAttachIndex;
					}
					else if(attach.usage == AttachmentUsage::Present)
						attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				}
				else if(attach.type == AttachmentType::Depth)
				{
					attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					depthAttachRef.attachment = attachIndex;
				}

				if(attach.usage == AttachmentUsage::InputNext)
				{
					// Last attachment added: current or resolved.
					const uint32_t inputAttachIndex = static_cast<uint32_t>(attachmentDescs.size() - 1);
					inputAttachmentRefs.emplace_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
				}
			}

			const uint32_t subpassIndex = static_cast<uint32_t>(subpassDescriptions.size());
			VkSubpassDescription& vkSubpassDesc = subpassDescriptions.emplace_back(Intl::CreateSubpassDesc());

			vkSubpassDesc.pDepthStencilAttachment = &depthAttachRef;
			vkSubpassDesc.colorAttachmentCount = static_cast<uint32_t>(colorAttachmentRefs.size());
			vkSubpassDesc.pColorAttachments = colorAttachmentRefs.data();
			vkSubpassDesc.pResolveAttachments = resolveAttachmentRefs.data();

			if (subpassIndex > 0)
			{
				// Add input attachment from previous subpass.
				vkSubpassDesc.inputAttachmentCount = static_cast<uint32_t>(subpassInputAttachmentRefs[subpassIndex - 1].size());
				vkSubpassDesc.pInputAttachments = subpassInputAttachmentRefs[subpassIndex - 1].data();
			}

			// Subpass dependency.
			/*VkSubpassDependency& subpassDep =*/ subpassDependencies.emplace_back(Intl::CreateSubpassDependency(subpassIndex, subpassNum));
		}


		VkRenderPassCreateInfo vkCreateInfo{};
		vkCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		vkCreateInfo.pNext = nullptr;
		vkCreateInfo.flags = VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM;
		vkCreateInfo.attachmentCount = static_cast<uint32_t>(attachmentDescs.size());
		vkCreateInfo.pAttachments = attachmentDescs.data();
		vkCreateInfo.subpassCount = static_cast<uint32_t>(subpassDescriptions.size());
		vkCreateInfo.pSubpasses = subpassDescriptions.data();
		vkCreateInfo.dependencyCount = static_cast<uint32_t>(subpassDependencies.size());
		vkCreateInfo.pDependencies = subpassDependencies.data();

		Create(_device, vkCreateInfo);
	}
	
	void RenderPass::Create(const Device& _device, const VkRenderPassCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreateRenderPass(_device, &_vkInfo, nullptr, &mHandle), L"Failed to create render pass!");

		SA_LOG(L"RenderPass created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void RenderPass::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyRenderPass(_device, mHandle, nullptr));

		SA_LOG(L"RenderPass destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		mHandle = VK_NULL_HANDLE;
	}


	void RenderPass::Begin(const CommandBuffer& _cmd, const FrameBuffer& _fBuff)
	{
		const std::vector<VkClearValue>& clearValues = _fBuff.GetClearValues();

		VkRenderPassBeginInfo info{
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			.pNext = nullptr,
			.renderPass = mHandle,
			.framebuffer = _fBuff,
			.renderArea = VkRect2D{{0,0}, {1200, 900}}, // TODO: FIX
			.clearValueCount = static_cast<uint32_t>(clearValues.size()),
			.pClearValues = clearValues.data(),
		};

		vkCmdBeginRenderPass(_cmd, &info, VK_SUBPASS_CONTENTS_INLINE);
	}

	void RenderPass::NextSubpass(const CommandBuffer& _cmd)
	{
		SA_VK_API(vkCmdNextSubpass(_cmd, VK_SUBPASS_CONTENTS_INLINE));
	}

	void RenderPass::End(const CommandBuffer& _cmd)
	{
		SA_VK_API(vkCmdEndRenderPass(_cmd));
	}


	RenderPass::operator VkRenderPass() const noexcept
	{
		return mHandle;
	}
}
