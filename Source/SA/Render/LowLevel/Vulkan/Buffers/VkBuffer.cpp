// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/VkBuffer.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void Buffer::Create(const Device& _device, uint32_t _size, VkBufferUsageFlags _usage, VkMemoryPropertyFlags _memory)
	{
		// Buffer
		{
			const VkBufferCreateInfo info{
				.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.size = _size,
				.usage = _usage,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0u,
				.pQueueFamilyIndices = nullptr,
			};

			SA_VK_API(vkCreateBuffer(_device, &info, nullptr, &mHandle));
		}


		// Memory
		{
			VkMemoryRequirements memRequirements{};
			SA_VK_API(vkGetBufferMemoryRequirements(_device, mHandle, &memRequirements));

			const uint32_t memoryTypeIndex = FindMemoryType(_device, memRequirements.memoryTypeBits, _memory);

			const VkMemoryAllocateInfo allocInfo{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext = nullptr,
				.allocationSize = memRequirements.size,
				.memoryTypeIndex = memoryTypeIndex,
			};

			SA_VK_API(vkAllocateMemory(_device, &allocInfo, nullptr, &mDeviceMemory));
			
			SA_VK_API(vkBindBufferMemory(_device, mHandle, mDeviceMemory, 0));
		}

		SA_LOG(L"Buffer created.", Info, SA.Render.Vulkan, (L"Handle [%1], Memory [%2]", mHandle, mDeviceMemory));
	}

	void Buffer::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"Buffer destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1], Memory [%2]", mHandle, mDeviceMemory));
		
		SA_VK_API(vkDestroyBuffer(_device, mHandle, nullptr));
		SA_VK_API(vkFreeMemory(_device, mDeviceMemory, nullptr));
	}
}
