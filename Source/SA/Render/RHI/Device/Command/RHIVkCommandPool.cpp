// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHIVkCommandPool.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>

namespace SA::RND::RHI
{
	void VkCommandPool::Create(const Device* _device)
	{
		CommandPool::Create(_device);

		// TODO: Clean
		mHandle.Create(_device->API_Vulkan(), _device->API_Vulkan().queueMgr.graphics[0].GetFamilyIndex());
	}
	
	void VkCommandPool::Destroy(const Device* _device)
	{
		CommandPool::Destroy(_device);

		mHandle.Destroy(mDevice->API_Vulkan());
	}


	const VK::CommandPool& VkCommandPool::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
