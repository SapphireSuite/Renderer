// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD
#define SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD

#include <cstdint>

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
		enum TextureUsage : uint8_t
		{
			//None = 0,

			/// Texture used as render target.
			RenderTarget = (1 << 0),

			/// Texture used as depth attachment/render target.
			Depth = (1 << 1),

			/// Texture used as input attachment in next subpass.
			Input = (1 << 2),

			/// TExture used as Shader Resource.
			SRV = (1 << 3),

			/// Texture used as Unordered Access.
			UAV = (1 << 4),

			/// Texture used as present image.
			Present = (1 << 5),
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkImageUsageFlags API_GetTextureUsage(uint8_t _usage);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		D3D12_RESOURCE_FLAGS API_GetTextureUsage(uint8_t _usage);
		uint8_t API_GetTextureUsage(D3D12_RESOURCE_FLAGS _d12Flags);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_TEXTURE_USAGE_GUARD
