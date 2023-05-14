// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Descriptors/RenderTargetDescriptor.hpp>

namespace SA::RND
{
	namespace RHI
	{
		DepthTargetDescriptor::DepthTargetDescriptor()
		{
			// Default values.
			format = Format::D16_UNORM;
			bInputNext = false;
		}
	}

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

		void API_AppendRenderTargetDescriptor(
			const RHI::RenderTargetDescriptor& _RTDesc,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			std::vector<VkAttachmentReference>& _colorAttachmentRefs,
			std::vector<VkAttachmentReference>& _resolveAttachmentRefs,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		)
		{
			const VkFormat format = API_GetFormat(_RTDesc.format);
			const VkAttachmentLoadOp loadOp = API_GetRenderTargetLoadOp(_RTDesc.loadMode);

			const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
			VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(format, _vkSampling, loadOp));

			/*VkAttachmentReference& colorAttachRef =*/ _colorAttachmentRefs.emplace_back(VkAttachmentReference{ attachIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
			VkAttachmentReference& resolveAttachRef = _resolveAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });

			if(_vkSampling != VK_SAMPLE_COUNT_1_BIT)
			{
				// Color attachment multisampling resolution.

				const uint32_t resolvAttachIndex = static_cast<uint32_t>(_subpassAttachments.size());
				VkAttachmentDescription& resolveAttachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(format, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

				if (RHI::IsPresentFormat(_RTDesc.format))
					resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

				resolveAttachRef.attachment = resolvAttachIndex;
			}
			else if(RHI::IsPresentFormat(_RTDesc.format))
				attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			if(_RTDesc.bInputNext)
			{
				// Last attachment added: current or resolved.
				const uint32_t inputAttachIndex = static_cast<uint32_t>(_subpassAttachments.size() - 1);
				_inputAttachmentRefs.push_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
			}
		}

		void API_AppendDepthTargetDescriptor(
			const RHI::DepthTargetDescriptor& _depthDesc,
			VkSampleCountFlagBits _vkSampling,
			std::vector<VkAttachmentDescription>& _subpassAttachments,
			VkAttachmentReference& _depthAttachRef,
			std::vector<VkAttachmentReference>& _inputAttachmentRefs
		)
		{
			if(!_depthDesc.bEnabled)
				return;

			const VkFormat format = API_GetFormat(_depthDesc.format);
			const VkAttachmentLoadOp loadOp = API_GetRenderTargetLoadOp(_depthDesc.loadMode);

			const uint32_t attachIndex = static_cast<uint32_t>(_subpassAttachments.size());
			VkAttachmentDescription& attachDesc = _subpassAttachments.emplace_back(Intl::CreateAttachment(format, _vkSampling, loadOp));

			attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			_depthAttachRef.attachment = attachIndex;

			if(_depthDesc.bInputNext)
			{
				// Last attachment added: current or resolved.
				const uint32_t inputAttachIndex = static_cast<uint32_t>(_subpassAttachments.size() - 1);
				_inputAttachmentRefs.push_back(VkAttachmentReference{ inputAttachIndex, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
			}
		}
	}

#endif
}