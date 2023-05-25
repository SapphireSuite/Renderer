// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_DEVICE_GUARD
#define SAPPHIRE_RENDER_D12_DEVICE_GUARD

#include "D12DeviceInfo.hpp"
#include "D12DeviceRequirements.hpp"
#include "Queue/D12QueueMgr.hpp"

namespace SA::RND::DX12
{
	class Factory;

	class Device
	{
		/// Logical device handle.
		LogicalDevice mLogicalDevice = nullptr;

		/// Physical device handle.
		PhysicalDevice mPhysicalDevice = nullptr;

	public:
		QueueMgr queueMgr;

		void Create(const DeviceInfo& _info);
		void Destroy();

		static std::vector<DeviceInfo> QueryDeviceInfos(const Factory& _factory,
			const DeviceRequirements& _reqs = DeviceRequirements{});

		operator ID3D12Device* () noexcept;
	};
}

#endif // SAPPHIRE_RENDER_D12_DEVICE_GUARD
