// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/RHI/Common/Misc/RHIFormat.hpp>
#include <SA/Render/RHI/Common/Misc/RHISampling.hpp>
#include <SA/Render/RHI/Common/Texture/RHITextureUsage.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Texture/VkTextureDescriptor.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Texture/D12TextureDescriptor.hpp>

#endif

namespace SA::RND::RHI
{
	struct TextureDescriptor
	{
		Vec2ui extents;

		uint32_t mipLevels = 1u;

		Format format = Format::R8G8B8A8_UNORM;

		Sampling sampling = Sampling::S1Bit;

		uint8_t usage = TextureUsage::RenderTarget;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::TextureDescriptor API_Vulkan() const noexcept;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::TextureDescriptor API_DirectX12() const noexcept;

#endif
	};
}

#endif // SAPPHIRE_RENDER_COMMON_TEXTURE_DESCRIPTOR_GUARD
