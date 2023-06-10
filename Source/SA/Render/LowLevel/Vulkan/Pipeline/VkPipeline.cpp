// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/VkPipeline.hpp>

#include <Device/VkDevice.hpp>
#include <Pass/VkRenderPass.hpp>
#include <Pipeline/VkPipelineLayout.hpp>

namespace SA::RND::VK
{
	void Pipeline::Create(const Device& _device, const GraphicsPipelineInfo& _info)
	{
		// TODO: Clean.
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			.primitiveRestartEnable = VK_FALSE
		};

		VkViewport viewport{
			.x = 0.0f,
			.y = 900.0f,
			.width = 1200.0f,
			.height = -900.0f,
			.minDepth = 0.0f,
			.maxDepth = 1.0f,
		};

		VkRect2D scissor{
			.offset = VkOffset2D{ 0, 0 },
			.extent = VkExtent2D{ 1200, 900 },
		};

		VkPipelineViewportStateCreateInfo viewportStateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.viewportCount = 1u,
			.pViewports = &viewport,
			.scissorCount = 1u,
			.pScissors = &scissor,
		};

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

		SA_LOG(L"Pipeline created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void Pipeline::Destroy(const Device& _device)
	{
		SA_VK_API(vkDestroyPipeline(_device, mHandle, nullptr));

		SA_LOG(L"Pipeline destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
		
		mHandle = VK_NULL_HANDLE;
	}


	Pipeline::operator VkPipeline() const noexcept
	{
		return mHandle;
	}
}
