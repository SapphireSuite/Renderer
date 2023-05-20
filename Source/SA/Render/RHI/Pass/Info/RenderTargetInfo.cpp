// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RenderTargetInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

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

	void RenderTargetInfo::API_Vulkan(
		VkSampleCountFlagBits _vkSampling,
		std::vector<VkAttachmentDescription>& _subpassAttachments,
		std::vector<VkAttachmentReference>& _colorAttachmentRefs,
		VkAttachmentReference& _depthAttachRef,
		std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
		std::vector<VkAttachmentReference>& _inputAttachmentRefs
	) const
	{
		const VkFormat vkFormat = VK::API_GetFormat(format);
		const VkAttachmentLoadOp vkLoadOp = VK::API_GetAttachmentLoadOp(loadMode);

		const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
		VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(vkFormat, _vkSampling, vkLoadOp));

		if(type == AttachmentType::Color)
		{
			/*VkAttachmentReference& colorAttachRef =*/ _colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
			VkAttachmentReference& resolveAttachRef = _resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });

			if(_vkSampling != VK_SAMPLE_COUNT_1_BIT)
			{
				// Color attachment multisampling resolution.

				const uint32_t resolvAttachIndex = static_cast<uint32_t>(_subpassAttachments.size());
				VkAttachmentDescription& resolveAttachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(vkFormat, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

				if (usage == AttachmentUsage::Present)
					resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

				resolveAttachRef.attachment = resolvAttachIndex;
			}
			else if(usage == AttachmentUsage::Present)
				attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		}
		else if(type == AttachmentType::Depth)
		{
			attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			_depthAttachRef.attachment = attachIndex;
		}

		if(usage == AttachmentUsage::InputNext)
		{
			// Last attachment added: current or resolved.
			const uint32_t inputAttachIndex = static_cast<uint32_t>(_subpassAttachments.size() - 1);
			_inputAttachmentRefs.push_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
		}
	}

#endif
}