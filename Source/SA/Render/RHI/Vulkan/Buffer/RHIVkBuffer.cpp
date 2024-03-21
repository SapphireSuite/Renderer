// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffer/RHIVkBuffer.hpp>

#include <Device/RHIVkDevice.hpp>

namespace SA::RND::RHI
{
	void VkBuffer::Create(const Device* _device, uint64_t _size, BufferUsage _usage, const void* _src)
	{
		mDevice = _device;

		mHandle.Create(_device->API_Vulkan(),
			_size,
			VK::API_GetBufferUsage(_usage),
			VK::API_GetBufferMemoryProperties(_usage),
			_src);
	}

	void VkBuffer::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
		mDevice = nullptr;
	}

	
	void VkBuffer::UploadData(const void* _src, uint64_t _size, uint64_t _offset)
	{
		mHandle.UploadData(mDevice->API_Vulkan(), _src, _size, _offset);
	}
	
	void VkBuffer::ReadbackData(void* _dst, uint64_t _size, uint64_t _offset)
	{
		mHandle.ReadbackData(mDevice->API_Vulkan(), _dst, _size, _offset);
	}
}
