// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_BASE_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_BASE_GUARD

#include <cstdint>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class Device;

	class BufferBase
	{
	public:
		static uint32_t FindMemoryType(const Device& _device, uint32_t _typeFilter, VkMemoryPropertyFlags _properties);
	};
}

#endif // SAPPHIRE_RENDER_VK_BUFFER_BASE_GUARD
