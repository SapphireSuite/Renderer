// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>

SA::VK::Instance instance;
SA::VK::Device device;

void Init()
{
	SA::Debug::InitDefaultLogger();

	instance.Create();

	{
		std::vector<SA::VK::DeviceInfo> deviceInfos = instance.QueryDeviceInfos();
		device.Create(deviceInfos[0]);
	}
}

void Uninit()
{
	device.Destroy();
	instance.Destroy();
}

int main()
{
	Init();



	Uninit();

	return 0;
}
