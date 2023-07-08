// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIVkContext.hpp>

#include <Pass/RHIVkPass.hpp>
#include <Pass/RHIVkFrameBuffer.hpp>
#include <Shader/RHIVkShader.hpp>
#include <Pipeline/RHIVkPipelineLayout.hpp>
#include <Pipeline/RHIVkPipeline.hpp>
#include <Pipeline/RHIVkRenderViews.hpp>
#include <Device/Command/RHIVkCommandPool.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	Pass* VkContext::InstantiatePassClass()
	{
		return new VkPass();
	}

	FrameBuffer* VkContext::InstantiateFrameBufferClass()
	{
		return new VkFrameBuffer();
	}

	Shader* VkContext::InstantiateShaderClass()
	{
		return new VkShader();
	}

	RenderViews* VkContext::InstantiateRenderViewsClass()
	{
		return new VkRenderViews();
	}

	PipelineLayout* VkContext::InstantiatePipelineLayoutClass()
	{
		return new VkPipelineLayout();
	}

	Pipeline* VkContext::InstantiatePipelineClass()
	{
		return new VkPipeline();
	}

	CommandPool* VkContext::InstantiateCommandPoolClass()
	{
		return new VkCommandPool();
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
