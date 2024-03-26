// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkRenderPass.hpp>

#include <SA/Collections/Debug>

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
		const uint32_t maxAttachmentNum = static_cast<uint32_t>(subpassNum * 8);

		std::vector<VkSubpassDescription> subpassDescriptions;
		subpassDescriptions.reserve(subpassNum);
		std::vector<VkSubpassDependency> subpassDependencies;
		subpassDependencies.reserve(subpassNum);

		std::vector<VkAttachmentDescription> attachmentDescs;
		attachmentDescs.reserve(maxAttachmentNum);
		std::vector<VkAttachmentReference> depthAttachmentRefs;
		depthAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassColorAttachmentRefs;
		subpassColorAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassResolveAttachmentRefs;
		subpassResolveAttachmentRefs.reserve(subpassNum);
		std::vector<std::vector<VkAttachmentReference>> subpassInputAttachmentRefs;
		subpassInputAttachmentRefs.reserve(subpassNum);

		std::unordered_map<const Texture*, uint32_t> textureToAttachIndexMap;

		for (auto subpassIt = _info.subpasses.begin(); subpassIt != _info.subpasses.end(); ++subpassIt)
		{
			// Per-Subpass attachment refs.
			std::vector<VkAttachmentReference>& colorAttachmentRefs = subpassColorAttachmentRefs.emplace_back();
			colorAttachmentRefs.reserve(subpassIt->attachments.size());

			std::vector<VkAttachmentReference>& resolveAttachmentRefs = subpassResolveAttachmentRefs.emplace_back();
			resolveAttachmentRefs.reserve(subpassIt->attachments.size());

			std::vector<VkAttachmentReference>& inputAttachmentRefs = subpassInputAttachmentRefs.emplace_back();
			inputAttachmentRefs.reserve(subpassIt->inputs.size());

			VkAttachmentReference& depthAttachRef = depthAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
			//

			for (auto& attach : subpassIt->attachments)
			{
				const uint32_t attachIndex = static_cast<uint32_t>(attachmentDescs.size());
				textureToAttachIndexMap[attach.texture] = attachIndex;

				const TextureDescriptor& desc = _info.textureToDescriptorMap.at(attach.texture);
				const bool bHasStencilFormat = HasStencilComponent(desc.format);

				VkAttachmentReference& resolveAttachRef = resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });


				// Emplace Attachment Description.
				{
					VkAttachmentDescription& attachDesc = attachmentDescs.emplace_back(VkAttachmentDescription{
						.flags = 0u,
						.format = desc.format,
						.samples = desc.sampling,
						.loadOp = attach.loadOp,
						.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
						.stencilLoadOp = bHasStencilFormat ? VK_ATTACHMENT_LOAD_OP_LOAD : VK_ATTACHMENT_LOAD_OP_DONT_CARE,
						.stencilStoreOp = bHasStencilFormat ? VK_ATTACHMENT_STORE_OP_STORE : VK_ATTACHMENT_STORE_OP_DONT_CARE,
						.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,	// Set later.
						.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED,	// Set later.
						});

					// Initial Layout
					{
						VkImageLayout initLayout = VK_IMAGE_LAYOUT_UNDEFINED;

						if (attach.accessMode == AttachmentAccessMode::ReadOnly)
						{
							if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
								initLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
							{
								if (bHasStencilFormat)
									initLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
								else
									initLayout = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
							}
						}
						else
						{
							for (auto prevSubpassIt = subpassIt; prevSubpassIt != _info.subpasses.begin();)
							{
								--prevSubpassIt;

								// Parse all previous subpass attachments (RT).
								for (auto& prevAttach : prevSubpassIt->attachments)
								{
									// Previously rendered and waiting for this (second) render.
									if (prevAttach.texture == attach.texture)
									{
										if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
											initLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
										else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
										{
											if (bHasStencilFormat)
												initLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
											else
												initLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
										}

										break;
									}
								}

								// Init layout already found.
								if (initLayout != VK_IMAGE_LAYOUT_UNDEFINED)
									break;

								// Parse all previous subpass input attachments.
								for (auto& prevInputTexture : prevSubpassIt->inputs)
								{
									if (prevInputTexture == attach.texture)
									{
										if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
											initLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
										else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
										{
											if (bHasStencilFormat)
												initLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
											else
												initLayout = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
										}
									}
								}
							}
						}

						attachDesc.initialLayout = initLayout;
					}

					// Final layout
					{
						VkImageLayout nextLayout = VK_IMAGE_LAYOUT_UNDEFINED;

						for (auto nextSubpassIt = subpassIt + 1; nextSubpassIt != _info.subpasses.end(); ++nextSubpassIt)
						{
							// Parse all next subpass attachments (RT).
							for (auto& nextAttach : nextSubpassIt->attachments)
							{
								if (nextAttach.texture == attach.texture)
								{
									switch (nextAttach.accessMode)
									{
										case AttachmentAccessMode::ReadWrite:
										{
											if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
												nextLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
											else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
											{
												if (bHasStencilFormat)
													nextLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
												else
													nextLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
											}

											break;
										}
										case AttachmentAccessMode::ReadOnly:
										{
											if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
												nextLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
											else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
											{
												if (bHasStencilFormat)
													nextLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
												else
													nextLayout = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
											}

											break;
										}
										default:
										{
											SA_LOG((L"AttachmentAccessMode [%1] not supported yet!", nextAttach.accessMode), Error, SA.Render.Vulkan);
											break;
										}
									}
								}
							}

							// Next layout already found.
							if (nextLayout != VK_IMAGE_LAYOUT_UNDEFINED)
								break;

							// Parse all next subpass input attachments.
							for (auto& nextInputTexture : nextSubpassIt->inputs)
							{
								if (nextInputTexture == attach.texture)
								{
									if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
										nextLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
									else if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
									{
										if (bHasStencilFormat)
											nextLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
										else
											nextLayout = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
									}
								}
							}
						}

						// TODO: default value if not found?

						attachDesc.finalLayout = nextLayout;
					}
				}


				// Attachments refs.
				{
					if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
					{
						depthAttachRef.layout = bHasStencilFormat ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
						resolveAttachRef.layout = bHasStencilFormat ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

						// Emplace depth attachment ref.
						depthAttachRef.attachment = attachIndex;
					}
					else if (desc.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
					{
						// Emplace color attachment ref.
						colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
					}
				}


				// Multisampling resolution.
				{
					if (desc.sampling != VK_SAMPLE_COUNT_1_BIT && attach.resolved)
					{
						const TextureDescriptor& resolvedDesc = _info.textureToDescriptorMap.at(attach.resolved);
						SA_ASSERT((Default, resolvedDesc.sampling == VK_SAMPLE_COUNT_1_BIT), SA.Render.Vulkan, L"Resolved texture must have 1 sample!")

						// TODO:
					}
				}
			}
		}
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