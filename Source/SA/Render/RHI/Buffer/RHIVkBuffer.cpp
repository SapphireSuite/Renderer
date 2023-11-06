// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffer/RHIVkBuffer.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkBuffer::Create(const Device* _device, uint64_t _size, BufferUsage _usage, const void* _src)
	{
		mHandle.Create(_device->API_Vulkan(),
			_size,
			VK::API_GetBufferUsage(_usage),
			VK::API_GetBufferMemoryProperties(_usage),
			_src);
	}

	void VkBuffer::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
