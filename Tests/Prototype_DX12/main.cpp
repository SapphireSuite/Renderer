// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/LowLevel/DX12/D12Factory.hpp>
#include <SA/Render/LowLevel/DX12/Device/D12Device.hpp>
using namespace SA::RND;

DX12::Factory factory;
DX12::Device device;

void Init()
{
	SA::Debug::InitDefaultLogger();

	// Render
	{
		factory.Create();

		// Device
		{
			std::vector<DX12::DeviceInfo> deviceInfos = factory.QueryDeviceInfos();
			device.Create(deviceInfos[0]);
		}
	}
}

void Uninit()
{
	device.Destroy();

	factory.Destroy();
}

int main()
{
	Init();



	Uninit();

	return 0;
}
