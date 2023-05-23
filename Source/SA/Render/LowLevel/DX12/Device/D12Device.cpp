// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/D12Device.hpp>

#include <D12Factory.hpp>

#include "../Debug/D12ValidationLayers.hpp"

namespace SA::RND::DX12
{
	void Device::Create(const DeviceInfo& _info)
	{
		mPhysicalDevice = _info.physicalDevice;

		SA_LOG(L"Physical device created.", Info, SA.Render.DX12, (L"Handle [%1]", mPhysicalDevice.Get()));

		SA_DX12_API(D3D12CreateDevice(mPhysicalDevice.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mLogicalDevice)),
			L"Failed to create logical device!")

		SetDebugName(mLogicalDevice, SA::StringFormat("SA:: Device {%1} [%2]", _info.desc.Description, _info.desc.DeviceId));

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

		SA_LOG(L"Logical device created.", Info, SA.Render.DX12, (L"Handle [%1]", mLogicalDevice));
	}
	
	void Device::Destroy()
	{
		if(mLogicalDevice)
		{
			mLogicalDevice->Release();
			
			SA_LOG(L"Logical device destroyed", Info, SA.Render.DX12, (L"Handle [%1]", mLogicalDevice));
			
			mLogicalDevice = nullptr;
		}

		if(mPhysicalDevice)
		{
			SA_LOG(L"Physical device destroyed", Info, SA.Render.DX12, (L"Handle [%1]", mPhysicalDevice.Get()));

			// ComPtr already call Release.
			mPhysicalDevice = nullptr;
		}
	}


//{ Query Device

	bool CheckDX12Support(const PhysicalDevice& _adapter)
	{
		// Try create device to check whether the adapter supports Direct3D 12.
		return SUCCEEDED(D3D12CreateDevice(_adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr));
	}

	std::vector<DeviceInfo> Device::QueryDeviceInfos(const Factory& _factory)
	{
		std::vector<DeviceInfo> result;
		result.reserve(5);

		UINT index = 0;
		PhysicalDevice adapter = nullptr;

		while (SUCCEEDED(_factory->EnumAdapterByGpuPreference(index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter))))
		{

			if (CheckDX12Support(adapter))
			{
				DeviceInfo& info = result.emplace_back();
				info.SetPhysicalDevice(adapter);
				info.Evaluate();
			}

			++index;
		}
		

		std::sort(result.begin(), result.end(), DeviceInfo::SortByScore);

		SA_WARN(!result.empty(), SA.Render.DX12, L"No suitable graphic device found!");

		return result;
	}

//}

}
