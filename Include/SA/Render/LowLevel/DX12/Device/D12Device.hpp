// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_DEVICE_GUARD
#define SAPPHIRE_RENDER_D12_DEVICE_GUARD

#include "D12DeviceInfo.hpp"

namespace SA::RND::DX12
{
	class Factory;

	class Device
	{
		/// Logical device handle.
		Microsoft::WRL::ComPtr<ID3D12Device> mLogicalDevice = nullptr;

		/// Physical device handle.
		PhysicalDevice mPhysicalDevice = nullptr;

	public:
		void Create(const DeviceInfo& _info);
		void Destroy();

		static std::vector<DeviceInfo> QueryDeviceInfos(const Factory& _factory);

		operator ID3D12Device* () noexcept;
	};
}

#endif // SAPPHIRE_RENDER_D12_DEVICE_GUARD
