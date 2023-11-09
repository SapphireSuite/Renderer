// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class ShaderBindingType : uint8_t
		{
			/// Vk::Uniform / DX::Constant buffer binding
			UniformConstantBuffer,

			StorageBuffer,

			Texture,

			Sampler,

			InputAttachment,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	
	namespace VK
	{
		VkDescriptorType API_GetDescriptorType(RHI::ShaderBindingType _type);
	}

#endif
}

#endif // SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD
