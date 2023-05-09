// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkRenderPass.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void RenderPass::Create(const Device& _device, const RenderPassInfo& _info)
	{
		VkRenderPassCreateInfo vkCreateInfo{};
		vkCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		vkCreateInfo.pNext = nullptr;
		vkCreateInfo.flags = VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM;
		vkCreateInfo.attachmentCount = static_cast<uint32_t>(_info.subpassAttachments.size());
		vkCreateInfo.pAttachments = _info.subpassAttachments.data();
		vkCreateInfo.subpassCount = static_cast<uint32_t>(_info.subpassDescriptions.size());
		vkCreateInfo.pSubpasses = _info.subpassDescriptions.data();
		vkCreateInfo.dependencyCount = static_cast<uint32_t>(_info.subpassDependencies.size());
		vkCreateInfo.pDependencies = _info.subpassDependencies.data();

		Create(_device, vkCreateInfo);
	}
	
	void RenderPass::Create(const Device& _device, const VkRenderPassCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreateRenderPass(_device, &_vkInfo, nullptr, &mHandle), L"Failed to create render pass!");

		SA_LOG(L"RenderPass created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void RenderPass::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"RenderPass destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		SA_VK_API(vkDestroyRenderPass(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}


	RenderPass::operator VkRenderPass() const noexcept
	{
		return mHandle;
	}
}
