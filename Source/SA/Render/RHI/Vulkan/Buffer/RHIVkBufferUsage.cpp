// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Buffer/RHIBufferUsage.hpp>

namespace SA::RND::VK
{
	VkBufferUsageFlags API_GetBufferUsage(RHI::BufferUsage _usage)
	{
		VkBufferUsageFlags vkFlags = 0;

		if (_usage & RHI::BufferUsageFlags::UniformBuffer)
			vkFlags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		if (_usage & RHI::BufferUsageFlags::StorageBuffer)
			vkFlags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		if (_usage & RHI::BufferUsageFlags::VertexBuffer)
			vkFlags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		if (_usage & RHI::BufferUsageFlags::IndexBuffer)
			vkFlags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

		return vkFlags;
	}

	VkMemoryPropertyFlags API_GetBufferMemoryProperties(RHI::BufferUsage _usage)
	{
		VkMemoryPropertyFlags vkFlags = 0;

		if ((_usage & RHI::BufferUsageFlags::CPUUpload) || (_usage & RHI::BufferUsageFlags::CPUReadBack))
			vkFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		else
			vkFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

		return vkFlags;
	}
}
