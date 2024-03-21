// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_DEVICE_GUARD
#define SAPPHIRE_RENDER_RHI_D12_DEVICE_GUARD

#include <SA/Render/RHI/Common/Device/RHIDevice.hpp>

#include "RHID12DeviceInfo.hpp"

#include <SA/Render/LowLevel/DX12/Device/D12Device.hpp>

namespace SA::RND::RHI
{
	class D12Device : public RHI::Device
	{
		DX12::Device mHandle;

	protected:
		Context* InstantiateContextClass() override final;

	public:
		void Create(const DeviceInfo* _info) override final;
		void Destroy() override final;

		void WaitIdle() override final;

		const DX12::Device& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_DEVICE_GUARD
