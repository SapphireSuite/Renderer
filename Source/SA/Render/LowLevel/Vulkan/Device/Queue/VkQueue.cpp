// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueue.hpp>

#include <Device/VkDevice.hpp>

namespace SA::VK
{
	uint32_t Queue::GetFamilyIndex() const noexcept
	{
		return mFamilyIndex;
	}

	void Queue::Create(const Device& _device, const QueueInfo& _info)
	{
		SA_ASSERT((Default, _info.familyIndex != ~uint32_t()), SA.Render.Vulkan, L"Invalid queue family index: -1");
		
		mFamilyIndex = _info.familyIndex;
		SA_VK_API(vkGetDeviceQueue(_device, _info.familyIndex, _info.queueIndex, &mHandle));

		SA_LOG(L"Queue created.", Info, SA.Render.Vulkan, (L"Handle [%1], Family [%2]", mHandle, mFamilyIndex));
	}
	
	void Queue::Destroy()
	{
		SA_LOG_RAII(L"Queue destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1], Family [%2]", mHandle, mFamilyIndex));

		mHandle = VK_NULL_HANDLE;
		mFamilyIndex = ~uint32_t();
	}


	Queue::operator VkQueue() const
	{
		return mHandle;
	}
}
