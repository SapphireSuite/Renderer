// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIVkContext.hpp>

#include <Pass/RHIVkPass.hpp>
#include <Pass/RHIVkFrameBuffer.hpp>
#include <Shader/RHIVkShader.hpp>

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
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
