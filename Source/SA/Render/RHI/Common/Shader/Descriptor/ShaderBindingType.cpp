// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/Descriptor/ShaderBindingType.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		constexpr VkDescriptorType sDescriptorTypeMap[]{
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
			VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
			VK_DESCRIPTOR_TYPE_SAMPLER,
			VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		};

		VkDescriptorType API_GetDescriptorType(RHI::ShaderBindingType _type)
		{
			SA_ASSERT((OutOfRange, (uint32_t)_type, 0u, sizeof(sDescriptorTypeMap)), SA.Render.Vulkan,
				(L"ShaderBindingType value [%1] invalid", (uint32_t)_type));

			return sDescriptorTypeMap[(uint32_t)_type];
		}
	}

#endif
}
