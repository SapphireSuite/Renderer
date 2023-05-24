// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_DEVICE_GUARD
#define SAPPHIRE_RENDER_D12_DEVICE_GUARD

#include "D12DeviceInfo.hpp"
#include "D12DeviceRequirements.hpp"

namespace SA::RND::DX12
{
	class Factory;

	class Device
	{
		/// Logical device handle.
		LogicalDevice mLogicalDevice = nullptr;

		/// Physical device handle.
		PhysicalDevice mPhysicalDevice = nullptr;

		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> mGraphicsQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> mComputeQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> mTransferQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> mPresentQueues;

	public:
		void Create(const DeviceInfo& _info);
		void Destroy();

		ID3D12CommandQueue* GetGraphicsQueue(uint32_t _index);
		ID3D12CommandQueue* GetComputeQueue(uint32_t _index);
		ID3D12CommandQueue* GetTransferQueue(uint32_t _index);
		ID3D12CommandQueue* GetPresentQueue(uint32_t _index);

		static std::vector<DeviceInfo> QueryDeviceInfos(const Factory& _factory,
			const DeviceRequirements& _reqs = DeviceRequirements{});

		operator ID3D12Device* () noexcept;
	};
}

#endif // SAPPHIRE_RENDER_D12_DEVICE_GUARD
