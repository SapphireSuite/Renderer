// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD

#include <SA/Render/RHI/Texture/RHITexture.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::RHI
{
	class VkTexture : public Texture
	{
		VK::Texture mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) override final;
		void Destroy(const Device* _device) override final;

		const VK::Texture& API_Vulkan() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD
