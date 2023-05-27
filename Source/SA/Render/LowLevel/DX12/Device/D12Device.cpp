// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/D12Device.hpp>

#include <D12Factory.hpp>
#include <Device/D12DeviceRequirements.hpp>

#include "../Debug/D12ValidationLayers.hpp"

namespace SA::RND::DX12
{
	void Device::Create(const DeviceInfo& _info)
	{
		mPhysicalDevice = _info.physicalDevice;

		SA_LOG(L"Physical device created.", Info, SA.Render.DX12, (L"Handle [%1]", mPhysicalDevice.Get()));

		mLogicalDevice = _info.logicalDevice;

		SetDebugName(mLogicalDevice.Get(), SA::StringFormat("SA:: Device {%1} [%2]", _info.desc.Description, _info.desc.DeviceId));

#if SA_DX12_VALIDATION_LAYERS

			ID3D12InfoQueue1* infoQueue = nullptr;

			if (mLogicalDevice->QueryInterface(IID_PPV_ARGS(&infoQueue)) == S_OK)
			{
				infoQueue->RegisterMessageCallback(ValidationLayers::DebugCallback,
					D3D12_MESSAGE_CALLBACK_IGNORE_FILTERS, nullptr, nullptr);

				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

				infoQueue->Release();
			}
			else
				SA_LOG(L"Device query info queue to enable validation layers failed.", Error, SA.Render.DX12);

#endif // SA_DX12_VALIDATION_LAYERS

		queueMgr.Create(_info);

		SA_LOG(L"Logical device created.", Info, SA.Render.DX12, (L"Handle [%1]", mLogicalDevice.Get()));
	}
	
	void Device::Destroy()
	{
		queueMgr.Destroy();

		if(mLogicalDevice)
		{
			SA_LOG_RAII(L"Logical device destroyed", Info, SA.Render.DX12, (L"Handle [%1]", mLogicalDevice.Get()));
			
			mLogicalDevice.Reset();
		}

		if(mPhysicalDevice)
		{
			SA_LOG_RAII(L"Physical device destroyed", Info, SA.Render.DX12, (L"Handle [%1]", mPhysicalDevice.Get()));

			mPhysicalDevice.Reset();
		}
	}


//{ Query Device

	std::vector<DeviceInfo> Device::QueryDeviceInfos(const Factory& _factory,
			const DeviceRequirements& _reqs)
	{
		std::vector<DeviceInfo> result;
		result.reserve(5);

		UINT index = 0;
		PhysicalDevice adapter = nullptr;

		while (SUCCEEDED(_factory->EnumAdapterByGpuPreference(index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter))))
		{
			DeviceInfo info;
			info.SetPhysicalDevice(adapter);

			if (info.TryCreateLogicalDevice() &&
				info.QueryQueueFamilies(_reqs.queue) >= 0)
			{
				info.Evaluate();
				result.emplace_back(std::move(info));
			}

			++index;
		}
		

		std::sort(result.begin(), result.end(), DeviceInfo::SortByScore);

		SA_WARN(!result.empty(), SA.Render.DX12, L"No suitable graphic device found!");

		return result;
	}

//}

	ID3D12Device* Device::operator->() const
	{
		return mLogicalDevice.Get();
	}
}
