// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkRenderPass.hpp>

#include <Device/VkDevice.hpp>
#include <Device/Command/VkCommandBuffer.hpp>
#include <Pass/VkFrameBuffer.hpp>

namespace SA::RND::VK
{
	namespace Intl
	{
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
	}

	void RenderPass::Create(const Device& _device, const RenderPassInfo& _info)
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

		std::unordered_map<Texture*, uint32_t> textureToAttachIndexMap;

		//for(auto& subpass : _info.subpasses)
		for (auto subpassIt = _info.subpasses.begin(); subpassIt != _info.subpasses.end(); ++subpassIt)
		{
			auto& subpass = *subpassIt;
		
			// Per-Subpass attachment refs.
			std::vector<VkAttachmentReference>& colorAttachmentRefs = subpassColorAttachmentRefs.emplace_back();
			colorAttachmentRefs.reserve(subpass.attachments.size());

			std::vector<VkAttachmentReference>& resolveAttachmentRefs = subpassResolveAttachmentRefs.emplace_back();
			resolveAttachmentRefs.reserve(subpass.attachments.size());
			
			std::vector<VkAttachmentReference>& inputAttachmentRefs = subpassInputAttachmentRefs.emplace_back();
			inputAttachmentRefs.reserve(subpass.inputs.size());

			VkAttachmentReference& depthAttachRef = depthAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
			//

			for(auto& attach: subpass.attachments)
			{
				const TextureDescriptor& desc = attach.texture->GetDescriptor();

				const uint32_t attachIndex = static_cast<uint32_t>(attachmentDescs.size());
				textureToAttachIndexMap[attach.texture] = attachIndex;
				VkAttachmentDescription& attachDesc = attachmentDescs.emplace_back(VkAttachmentDescription{
					.flags = 0u,
					.format = desc.format,
					.samples = desc.sampling,
					.loadOp = VK::API_GetAttachmentLoadOp(attach.loadMode),
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK::API_GetAttachmentLoadOp(attach.loadMode),
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
					.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				});
				VkAttachmentReference& resolveAttachRef = resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
				
				if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
				{
					attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					resolveAttachRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

					// Emplace depth attachment ref.
					depthAttachRef.attachment = attachIndex;
				}
				else if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
				{
					// Emplace color attachment ref.
					colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
				}
				
				// For any render target.
				//if (desc.usage & TextureUsage::RenderTarget)
				{
					// Multisampling resolution.
					if (desc.sampling != VK_SAMPLE_COUNT_1_BIT && attach.resolved)
					{
						const TextureDescriptor& resolvedDesc = attach.resolved->GetDescriptor();

						SA_ASSERT((Default, resolvedDesc.sampling == VK_SAMPLE_COUNT_1_BIT), SA.Render.Vulkan, L"Resolved texture must have 1 sample!")

						const uint32_t resolvAttachIndex = static_cast<uint32_t>(attachmentDescs.size());
						resolveAttachRef.attachment = resolvAttachIndex;
						textureToAttachIndexMap[attach.resolved] = resolvAttachIndex;
						VkAttachmentDescription& resolveAttachDesc = attachmentDescs.emplace_back(VkAttachmentDescription{
							.flags = 0u,
							.format = resolvedDesc.format,
							.samples = VK_SAMPLE_COUNT_1_BIT,
							.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
							.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
							.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
							.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
							.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
							.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
						});

						if (resolvedDesc.usage & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
						{
							if(resolvedDesc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
								resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
							else
								resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						}
						else if (IsPresentFormat(resolvedDesc.format))
							resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					}
					else if (IsPresentFormat(desc.format))
						attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				}
			}

			for (auto& input : subpass.inputs)
			{
				auto findIt = textureToAttachIndexMap.find(input);

				SA_ASSERT((Default, findIt != textureToAttachIndexMap.end()), SA.Render.Vulkan, L"Input Attachment not found in previous subpass render targets!");

				const uint32_t attachIndex = textureToAttachIndexMap[input];

				const TextureDescriptor& inputDesc = input->GetDescriptor();

				inputAttachmentRefs.emplace_back(VkAttachmentReference{
					attachIndex,
					(inputDesc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
				});
			}

			const uint32_t subpassIndex = static_cast<uint32_t>(subpassDescriptions.size());
			/*VkSubpassDescription& vkSubpassDesc = */subpassDescriptions.emplace_back(VkSubpassDescription{
				.flags = 0u,
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.inputAttachmentCount = static_cast<uint32_t>(inputAttachmentRefs.size()),
				.pInputAttachments = inputAttachmentRefs.data(),
				.colorAttachmentCount = static_cast<uint32_t>(colorAttachmentRefs.size()),
				.pColorAttachments = colorAttachmentRefs.data(),
				.pResolveAttachments = resolveAttachmentRefs.data(),
				.pDepthStencilAttachment = &depthAttachRef,
				.preserveAttachmentCount = 0u,
				.pPreserveAttachments = nullptr,
			});

			// Subpass dependency.
			// TODO: Rework
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
		const Vec2ui& extents = _fBuff.GetExtents();
		const std::vector<VkClearValue>& clearValues = _fBuff.GetClearValues();

		VkRenderPassBeginInfo info{
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			.pNext = nullptr,
			.renderPass = mHandle,
			.framebuffer = _fBuff,
			.renderArea = VkRect2D{{0,0}, {extents.x, extents.y}}, // TODO: CLEAN
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
