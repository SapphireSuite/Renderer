// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD

#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::RHI
{
	class VkTexture : public Texture
	{
		VK::Texture mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) override final;
		void Create(const Device* _device, const TextureDescriptor& _desc) override final;
		void CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex) override final;
		void Destroy(const Device* _device) override final;

		VK::Texture& API_Vulkan() override final;
		const VK::Texture& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_TEXTURE_GUARD
