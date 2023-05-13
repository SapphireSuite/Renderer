// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/RHIVkShader.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	const VK::Shader& VkShader::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif
