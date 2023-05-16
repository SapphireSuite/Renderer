// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIVkDevice.hpp>

#include <Context/RHIVkContext.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkDevice::Create(const DeviceInfo* _info)
	{
		SA_ASSERT((Nullptr, _info), SA.Render.RHI.Vulkan);

		mHandle.Create(*_info->API_Vulkan());
	}
	
	void VkDevice::Destroy()
	{
		mHandle.Destroy();
	}


	Context* VkDevice::InstantiateContextClass()
	{
		return new VkContext();
	}


	const VK::Device* VkDevice::API_Vulkan() const
	{
		return &mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
