// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipeline.hpp>

#include <Device/VkDevice.hpp>
#include <Device/Command/VkCommandBuffer.hpp>

#include <Pass/VkRenderPass.hpp>

#include <Pipeline/VkRenderViews.hpp>
#include <Pipeline/VkPipelineLayout.hpp>

namespace SA::RND::VK
{
	void Pipeline::Create(const Device& _device, const GraphicsPipelineInfo& _info)
	{
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			.primitiveRestartEnable = VK_FALSE
		};

		VkPipelineViewportStateCreateInfo viewportStateInfo = _info.views->MakeVkStateInfo();

		// TODO: Clean.
		VkPipelineColorBlendAttachmentState colorBlendAttachment{
			.blendEnable = VK_TRUE,
			.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
			.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
			.colorBlendOp = VK_BLEND_OP_ADD,
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
			.alphaBlendOp = VK_BLEND_OP_ADD,
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		};

		VkPipelineColorBlendStateCreateInfo colorBlendingInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.logicOpEnable = VK_FALSE,
			.logicOp = VK_LOGIC_OP_COPY,
			.attachmentCount = 1,
			.pAttachments = &colorBlendAttachment,
			.blendConstants = {0, 0, 0, 0},
		};


		constexpr VkDynamicState dynamicStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

		VkPipelineDynamicStateCreateInfo dynamicStateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState),
			.pDynamicStates = dynamicStates
		};
		//

		auto vkVertexInputState = _info.vertexInputState.MakeVkInfo();

		VkGraphicsPipelineCreateInfo vkCreateInfo{
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.stageCount = static_cast<uint32_t>(_info.shaderStages.size()),
			.pStages = _info.shaderStages.data(),
			.pVertexInputState = &vkVertexInputState,
			.pInputAssemblyState = &inputAssemblyInfo,
			.pTessellationState = nullptr,
			.pViewportState = &viewportStateInfo,
			.pRasterizationState = &_info.raster,
			.pMultisampleState = &_info.multisampling,
			.pDepthStencilState = &_info.depthStencil,
			.pColorBlendState = &colorBlendingInfo,
			.pDynamicState = &dynamicStateInfo,
			.layout = *_info.layout,
			.renderPass = *_info.renderPass,
			.subpass = _info.subpassIndex,
			.basePipelineHandle = VK_NULL_HANDLE,
			.basePipelineIndex = -1,
		};

		Create(_device, vkCreateInfo);
	}

	void Pipeline::Create(const Device& _device, const VkGraphicsPipelineCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &_vkInfo, nullptr, &mHandle),
			L"Failed to create graphics pipeline");

		mBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

		SA_LOG(L"Pipeline created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void Pipeline::Create(const Device& _device, const VkComputePipelineCreateInfo& _vkInfo)
	{
		SA_VK_API(vkCreateComputePipelines(_device, VK_NULL_HANDLE, 1, &_vkInfo, nullptr, &mHandle),
			L"Failed to create compute pipeline");

		mBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;

		SA_LOG(L"Pipeline created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void Pipeline::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyPipeline(_device, mHandle, nullptr));

		SA_LOG(L"Pipeline destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
		
		mHandle = VK_NULL_HANDLE;
	}


	void Pipeline::Bind(const CommandBuffer& _cmd)
	{
		SA_VK_API(vkCmdBindPipeline(_cmd, mBindPoint, mHandle));
	}


	Pipeline::operator VkPipeline() const noexcept
	{
		return mHandle;
	}
}
