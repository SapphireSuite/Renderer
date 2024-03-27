// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_TEXTURE_GUARD

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

#include "RHITextureDescriptor.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	namespace VK
	{
		class Texture;
	}
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	namespace DX12
	{
		class Texture;
	}
#endif

	namespace RHI
	{
		class Device;
		class ResourceInitializer;
		class Swapchain;

		class Texture
		{
		public:
			using TextureDescT = TextureDescriptor;

			virtual ~Texture() = default;

			/**
			* Create Texture from raw texture input.
			* Used as input texture for sampling.
			*/
			virtual void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) = 0;
			/**
			* Create Texture from descriptor
			* Used as framebuffer render target attachment.
			*/
			virtual void Create(const Device* _device, const TextureDescriptor& _desc) = 0;
			/**
			* Create Texture from image
			* Used as framebuffer render target attachment with present usage.
			*/
			virtual void CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual VK::Texture& API_Vulkan();
			virtual const VK::Texture& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual DX12::Texture& API_DirectX12();
			virtual const DX12::Texture& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_TEXTURE_GUARD
