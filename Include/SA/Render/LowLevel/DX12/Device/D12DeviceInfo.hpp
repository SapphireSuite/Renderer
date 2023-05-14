// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD

#include <SA/Render/LowLevel/Common/Device/DeviceInfo.hpp>

#include "D12PhysicalDevice.hpp"

namespace SA::RND::DX12
{
	struct DeviceInfo : public RND::DeviceInfo
	{
		DXGI_ADAPTER_DESC2 desc;
		PhysicalDevice physicalDevice = nullptr;

		void SetPhysicalDevice(PhysicalDevice _device);
	};
}

#endif // SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD
