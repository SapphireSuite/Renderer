// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;

	class Texture
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkDeviceMemory mMemory = VK_NULL_HANDLE;

	public:
		/// Create Texture from raw texture input.
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_TEXTURE_GUARD
