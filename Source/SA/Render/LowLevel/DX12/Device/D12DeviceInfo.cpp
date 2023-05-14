// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/D12DeviceInfo.hpp>

namespace SA::RND::DX12
{
	void DeviceInfo::SetPhysicalDevice(PhysicalDevice _device)
	{
		physicalDevice = _device;

		physicalDevice->GetDesc2(&desc);
	}

	void DeviceInfo::Evaluate()
	{
		// Not CGPU
		if((desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0)
			score += 1000;
	}
}
