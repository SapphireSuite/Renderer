// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_D12_DEVICE_INFO_GUARD

#include <SA/Render/RHI/Common/Device/RHIDeviceInfo.hpp>

#include <SA/Render/LowLevel/DX12/Device/D12DeviceInfo.hpp>

namespace SA::RND::RHI
{
	class D12DeviceInfo : public RHI::DeviceInfo
	{
		DX12::DeviceInfo mHandle;

	public:
		D12DeviceInfo() = default;
		D12DeviceInfo(DX12::DeviceInfo&& _handle);

		uint32_t GetScore() const override final;

		std::wstring GetName() const override final;

		uint32_t GetID() const override final;
		uint32_t GetVendorID() const override final;

		const DX12::DeviceInfo& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_DEVICE_INFO_GUARD
