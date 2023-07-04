// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipeline.hpp>

#include <Device/VkDevice.hpp>
#include <Device/Command/VkCommandBuffer.hpp>

#include <Pass/VkRenderPass.hpp>

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

		VkPipelineViewportStateCreateInfo viewportStateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.viewportCount = static_cast<uint32_t>(_info.views.viewports.size()),
			.pViewports = _info.views.viewports.data(),
			.scissorCount = static_cast<uint32_t>(_info.views.scissors.size()),
			.pScissors = _info.views.scissors.data(),
		};

		// TODO: Clean.
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.depthTestEnable = VK_TRUE,
			.depthWriteEnable = VK_TRUE,
			.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
			.depthBoundsTestEnable = VK_FALSE,
			.stencilTestEnable = VK_FALSE,
			.front = {},
			.back = {},
			.minDepthBounds = 0.0f,
			.maxDepthBounds = 1.0f,
		};

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
			.pDepthStencilState = &depthStencilInfo,
			.pColorBlendState = &colorBlendingInfo,
			.pDynamicState = nullptr,
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
