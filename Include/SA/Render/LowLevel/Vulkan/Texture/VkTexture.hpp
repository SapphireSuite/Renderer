// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

#include "VkTextureDescriptor.hpp"

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;
	class Swapchain;

	class Texture
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkDeviceMemory mMemory = VK_NULL_HANDLE;

	public:
		using TextureDescT = TextureDescriptor;

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

		void Destroy(const Device& _device);


		operator VkImage() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_TEXTURE_GUARD
