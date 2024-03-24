// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD
#define SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD

#include <SA/Support/Flags.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class TextureUsageFlags : uint8_t
		{
			None = 0,

			/// Texture used as color render target.
			Color = (1 << 0),

			/// Texture used as depth attachment/render target.
			Depth = (1 << 1),

			/// Texture used as input attachment in next subpass.
			Input = (1 << 2),
		};

		using TextureUsage = uint8_t;
		SA_DEFINE_ENUM_CLASS_FLAGS(TextureUsageFlags)
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkImageUsageFlags API_GetTextureUsage(RHI::TextureUsage _usage);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		D3D12_RESOURCE_FLAGS API_GetTextureUsage(RHI::TextureUsage _usage);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD