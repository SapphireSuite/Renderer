// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_TEXTURE_GUARD
#define SAPPHIRE_RENDER_D12_TEXTURE_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

#include "D12TextureDescriptor.hpp"

namespace SA::RND::DX12
{
	class Device;
	class ResourceInitializer;
	class Swapchain;

	class Texture
	{
		MComPtr<ID3D12Resource> mHandle;

	public:
		using TextureDescT = TextureDescriptor;

		MComPtr<ID3D12Resource> Get() const;

		/**
		* Create Texture from raw texture input.
		* Used as input texture for sampling.
		*/
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);

		/**
		* Create Texture from descriptor
		* Used as framebuffer attachment.
		*/
		void Create(const Device& _device, const TextureDescriptor& _desc);

		/**
		* Create texture from swapchain backbuffer image handle.
		* Used as frambuffer present attachment.
		*/
		void CreateFromImage(const Swapchain& _swapchain, uint32_t _imageIndex);

		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_D12_TEXTURE_GUARD
