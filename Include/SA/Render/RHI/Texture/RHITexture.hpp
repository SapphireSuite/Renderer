// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_TEXTURE_GUARD

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>
#include <SA/Render/LowLevel/Common/Texture/TextureDescriptor.hpp>

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
			virtual ~Texture() = default;

			/**
			* Create Texture from descriptor
			* Used as framebuffer attachment.
			*/
			virtual void Create(const Device* _device, const SA::RND::TextureDescriptor& _desc) = 0;
			/**
			* Create Texture from raw texture input.
			* Used as input texture for sampling.
			*/
			virtual void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) = 0;
			virtual void CreateFromImage(const Device* _device, const Swapchain* _swapchain, uint32_t _imageIndex) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::Texture& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::Texture& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_TEXTURE_GUARD
