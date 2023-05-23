// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include "D12Factory.hpp"

#include "Debug/D12ValidationLayers.hpp"
#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void Factory::Create()
	{
		UINT dxgiFactoryFlags = 0;

	#if SA_DX12_VALIDATION_LAYERS

		ValidationLayers::Initialize();

		// Enable additional debug layers.
		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

	#endif

		SA_DX12_API(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&mHandle)), L"Failed to create DX12 factory.");

		SA_LOG(L"Factory created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle));
	}
	
	void Factory::Destroy()
	{
		if (mHandle)
		{
			mHandle->Release();
			
			SA_LOG(L"Factory destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle));

			mHandle = nullptr;
		}

	#if SA_DX12_VALIDATION_LAYERS

		ValidationLayers::Uninitialize();

	#endif
	}

	std::vector<DeviceInfo> Factory::QueryDeviceInfos() const
	{
		return Device::QueryDeviceInfos(*this);
	}

	DXFactoryT Factory::operator->() const
	{
		return mHandle;
	}
}
