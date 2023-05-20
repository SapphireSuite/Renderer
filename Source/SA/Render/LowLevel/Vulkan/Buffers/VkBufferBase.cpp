// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/VkBufferBase.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	uint32_t BufferBase::FindMemoryType(const Device& _device, uint32_t _typeFilter, VkMemoryPropertyFlags _properties)
	{
		const VkPhysicalDeviceMemoryProperties& memProperties = _device.GetMemoryProperties();

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & _properties) == _properties)
				return i;
		}

		SA_LOG((L"Memory type [%1] requiered not supported!", _properties), Error, SA.Render.Vulkan);

		return ~uint32_t();
	}
}
