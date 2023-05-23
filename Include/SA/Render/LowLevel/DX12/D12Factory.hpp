// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_FACTORY_GUARD
#define SAPPHIRE_RENDER_DX12_FACTORY_GUARD

#include "DX12API.hpp"

#include "Device/D12DeviceInfo.hpp"

namespace SA::RND::DX12
{
	using DXFactoryT = Microsoft::WRL::ComPtr<IDXGIFactory6>;

	class Factory
	{
		DXFactoryT mHandle = nullptr;

	public:
		void Create();
		void Destroy();

		std::vector<DeviceInfo> QueryDeviceInfos() const;

		DXFactoryT operator->() const;
	};
}

#endif	// SAPPHIRE_RENDER_DX12_FACTORY_GUARD
