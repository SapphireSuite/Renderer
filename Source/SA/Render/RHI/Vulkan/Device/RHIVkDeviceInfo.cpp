// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIVkDeviceInfo.hpp>

namespace SA::RND::RHI
{
	VkDeviceInfo::VkDeviceInfo(VK::DeviceInfo&& _handle) :
		mHandle{ std::move(_handle) }
	{
	}


	uint32_t VkDeviceInfo::GetScore() const
	{
		return mHandle.score;
	}


	std::wstring VkDeviceInfo::GetName() const
	{
		return SA::ToWString(mHandle.physicalProperties.deviceName);
	}


	uint32_t VkDeviceInfo::GetID() const
	{
		return mHandle.physicalProperties.deviceID;

	}
	
	uint32_t VkDeviceInfo::GetVendorID() const
	{
		return mHandle.physicalProperties.vendorID;
	}


	const VK::DeviceInfo& VkDeviceInfo::API_Vulkan() const
	{
		return mHandle;
	}
}
