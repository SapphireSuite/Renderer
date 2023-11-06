// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/VkBuffer.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void Buffer::Create(const Device& _device,
		uint64_t _size,
		VkBufferUsageFlags _usage,
		VkMemoryPropertyFlags _memory,
		const void* _data)
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
#if SA_DEBUG
			mMemoryPropertyFlags = _memory;
#endif

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

		if (_data)
			UploadData(_device, _data, _size);

		SA_LOG(L"Buffer created.", Info, SA.Render.Vulkan, (L"Handle [%1], Memory [%2]", mHandle, mDeviceMemory));
	}

	void Buffer::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"Buffer destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1], Memory [%2]", mHandle, mDeviceMemory));
		
		SA_VK_API(vkDestroyBuffer(_device, mHandle, nullptr));
		SA_VK_API(vkFreeMemory(_device, mDeviceMemory, nullptr));
	}

	void Buffer::UploadData(const Device& _device, const void* _src, uint64_t _size, uint64_t _offset)
	{
		SA_ASSERT((Nullptr, _src), SA.Render.Vulkan);
#if SA_DEBUG
		SA_ASSERT((Default, (mMemoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) && (mMemoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)), SA.Render.Vulkan, L"Buffer must have `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT` and `VK_MEMORY_PROPERTY_HOST_COHERENT_BIT` flags to copy data from CPU to GPU");
#endif

		void* GPUData = nullptr;
		SA_VK_API(vkMapMemory(_device, mDeviceMemory, _offset, _size, 0, &GPUData));

		std::memcpy(GPUData, _src, _size);

		SA_VK_API(vkUnmapMemory(_device, mDeviceMemory));
	}

	void Buffer::ReadbackData(const Device& _device, void* _dst, uint64_t _size, uint64_t _offset)
	{
		SA_ASSERT((Nullptr, _dst), SA.Render.Vulkan);
#if SA_DEBUG
		SA_ASSERT((Default, (mMemoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) && (mMemoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)), SA.Render.Vulkan, L"Buffer must have `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT` and `VK_MEMORY_PROPERTY_HOST_COHERENT_BIT` flags to copy data from CPU to GPU");
#endif

		void* GPUData = nullptr;
		SA_VK_API(vkMapMemory(_device, mDeviceMemory, _offset, _size, 0, &GPUData));

		std::memcpy(_dst, GPUData, _size);

		SA_VK_API(vkUnmapMemory(_device, mDeviceMemory));
	}


	Buffer::operator VkBuffer() const
	{
		return mHandle;
	}
}
