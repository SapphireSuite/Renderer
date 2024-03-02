// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_VK_CUBEMAP_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawCubemap.hpp>

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;

	class Cubemap
	{
		VkImage mTextureImage = VK_NULL_HANDLE;
		VkDeviceMemory mTextureMemory = VK_NULL_HANDLE;

		VkImage mIrradianceImage = VK_NULL_HANDLE;
		VkDeviceMemory mIrradianceMemory = VK_NULL_HANDLE;

	public:
		/// Create Cubemap from raw cubemap input.
		void Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_CUBEMAP_GUARD
