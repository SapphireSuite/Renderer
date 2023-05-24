// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD

#include <SA/Render/LowLevel/Common/Device/DeviceInfoBase.hpp>

#include "D12PhysicalDevice.hpp"
#include "D12LogicalDevice.hpp"

namespace SA::RND::DX12
{
	struct DeviceInfo : public DeviceInfoBase
	{
//{ Physical Device

		DXGI_ADAPTER_DESC2 desc;
		PhysicalDevice physicalDevice = nullptr;

		void SetPhysicalDevice(PhysicalDevice _device);

//}

//{ Logical Device

		LogicalDevice logicalDevice = nullptr;

		/// Try create logical device from physical device to check DX12 support.
		bool TryCreateLogicalDevice();

//}

//{ Queues

		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> graphicsQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> computeQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> transferQueues;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandQueue>> presentQueues;

		int QueryQueueFamilies(QueueRequirements _queueReqs);

//}

		/// Evaluate device to compute score.
		void Evaluate();
	};
}

#endif // SAPPHIRE_RENDER_DX12_DEVICE_INFO_GUARD
