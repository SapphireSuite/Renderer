// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_TEXTURE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_TEXTURE_DESCRIPTOR_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Common/Misc/RHIFormat.hpp>
#include <SA/Render/RHI/Common/Misc/RHISampling.hpp>

#include "RHITextureUsage.hpp"

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

		Format format = Format::R8G8B8A8_UNORM;

		Sampling sampling = Sampling::S1Bit;

		TextureUsage usage = static_cast<TextureUsage>(TextureUsageFlags::Color); // TODO clean.

		Color clearColor = Color::black;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::TextureDescriptor API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::TextureDescriptor API_DirectX12() const noexcept;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_TEXTURE_DESCRIPTOR_GUARD
