// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIVkDevice.hpp>

#include <Context/RHIVkContext.hpp>

namespace SA::RND::RHI
{
	Context* VkDevice::InstantiateContextClass()
	{
		return new VkContext();
	}
	

	void VkDevice::Create(const DeviceInfo* _info)
	{
		SA_ASSERT((Nullptr, _info), SA.Render.RHI.Vulkan);

		mHandle.Create(_info->API_Vulkan());
	}
	
	void VkDevice::Destroy()
	{
		Device::Destroy();

		mHandle.Destroy();
	}


	void VkDevice::WaitIdle()
	{
		mHandle.WaitIdle();
	}


	const VK::Device& VkDevice::API_Vulkan() const
	{
		return mHandle;
	}
}
