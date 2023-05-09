// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/SubPassAttachmentDescriptor.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		namespace Intl
		{
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

		void API_AppendRenderSubPassAttachmentDescriptor(
			const RHI::SubPassAttachmentDescriptor& _RHIsubpassAttach,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			VkAttachmentReference& _depthAttachRef,
			std::vector<VkAttachmentReference>& _colorAttachmentRefs,
			std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		)
		{
			const VkFormat format = API_GetFormat(_RHIsubpassAttach.format);
			const VkAttachmentLoadOp loadOp = API_GetAttachmentLoadOp(_RHIsubpassAttach.loadMode);

			const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
			VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(format, _vkSampling, loadOp));

			if(RHI::IsDepthFormat(_RHIsubpassAttach.format))
			{
				attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				_depthAttachRef.attachment = attachIndex;
			}
			else
			{
				/*VkAttachmentReference& colorAttachRef =*/ _colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
				VkAttachmentReference& resolveAttachRef = _resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });

				if(_vkSampling != VK_SAMPLE_COUNT_1_BIT)
				{
					// Color attachment multisampling resolution.

					const uint32_t resolvAttachIndex = static_cast<uint32_t>(_subpassAttachments.size());
					VkAttachmentDescription& resolveAttachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(format, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

					if (RHI::IsPresentFormat(_RHIsubpassAttach.format))
						resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

					resolveAttachRef.attachment = resolvAttachIndex;
				}
				else if(RHI::IsPresentFormat(_RHIsubpassAttach.format))
					attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			}

			if(_RHIsubpassAttach.bInputNext)
				_inputAttachmentRefs.push_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
		}
	}

#endif
}