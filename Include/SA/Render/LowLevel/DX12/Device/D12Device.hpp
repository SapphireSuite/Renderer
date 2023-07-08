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

//{ Sync

		HANDLE mFenceEvent;
		uint64_t mFenceValue = 0;
		MComPtr<ID3D12Fence> mFence;

		void CreateSynchronisation();
		void DestroySynchronisation();

//}

#if SA_DX12_VALIDATION_LAYERS

		DWORD mVLayerCallbackCookie = 0;
#endif

	public:
		QueueMgr queueMgr;

		void Create(const DeviceInfo& _info);
		void Destroy();

		void WaitIdle();

		static std::vector<DeviceInfo> QueryDeviceInfos(const Factory& _factory,
			const DeviceRequirements& _reqs = DeviceRequirements{});

		ID3D12Device* operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_D12_DEVICE_GUARD
