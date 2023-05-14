// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/D12DeviceInfo.hpp>

namespace SA::RND::DX12
{
	void DeviceInfo::SetPhysicalDevice(PhysicalDevice _device)
	{
		physicalDevice = _device;

		physicalDevice->GetDesc2(&desc);
	}
}
