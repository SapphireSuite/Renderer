// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/RenderTargetDescriptor.hpp>

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

	void RenderTargetDescriptor::API_Vulkan(
		VkSampleCountFlagBits _vkSampling,
		std::vector<VkAttachmentDescription>& _subpassAttachments,
		std::vector<VkAttachmentReference>& _colorAttachmentRefs,
		std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
		std::vector<VkAttachmentReference>& _inputAttachmentRefs
	) const
	{
		const VkFormat vkFormat = VK::API_GetFormat(format);
		const VkAttachmentLoadOp vkLoadOp = VK::API_GetRenderTargetLoadOp(loadMode);

		const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
		VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(vkFormat, _vkSampling, vkLoadOp));

		/*VkAttachmentReference& colorAttachRef =*/ _colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
		VkAttachmentReference& resolveAttachRef = _resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });

		if(_vkSampling != VK_SAMPLE_COUNT_1_BIT)
		{
			// Color attachment multisampling resolution.

			const uint32_t resolvAttachIndex = static_cast<uint32_t>(_subpassAttachments.size());
			VkAttachmentDescription& resolveAttachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(vkFormat, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

			if (RHI::IsPresentFormat(format))
				resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			resolveAttachRef.attachment = resolvAttachIndex;
		}
		else if(RHI::IsPresentFormat(format))
			attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		if(bInputNext)
		{
			// Last attachment added: current or resolved.
			const uint32_t inputAttachIndex = static_cast<uint32_t>(_subpassAttachments.size() - 1);
			_inputAttachmentRefs.push_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
		}
	}

#endif


	DepthTargetDescriptor::DepthTargetDescriptor()
	{
		// Default values.
		format = Format::D16_UNORM;
		bInputNext = false;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	void DepthTargetDescriptor::API_VulkanDepth(
		VkSampleCountFlagBits _vkSampling,
		std::vector<VkAttachmentDescription>& _subpassAttachments,
		VkAttachmentReference& _depthAttachRef,
		std::vector<VkAttachmentReference>& _inputAttachmentRefs
	) const
	{
		if(!bEnabled)
			return;

		const VkFormat vkFormat = VK::API_GetFormat(format);
		const VkAttachmentLoadOp vkLoadOp = VK::API_GetRenderTargetLoadOp(loadMode);

		const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
		VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(vkFormat, _vkSampling, vkLoadOp));

		attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		_depthAttachRef.attachment = attachIndex;

		if(bInputNext)
		{
			// Last attachment added: current or resolved.
			const uint32_t inputAttachIndex = static_cast<uint32_t>(_subpassAttachments.size() - 1);
			_inputAttachmentRefs.push_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
		}
	}

#endif
}