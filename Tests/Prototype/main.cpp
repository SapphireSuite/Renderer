// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/RHI/RHIVkRenderInterface.hpp>
#include <SA/Render/RHI/RHID12RenderInterface.hpp>
using namespace SA::RND;

RHI::RenderInterface* intf;
RHI::Device* device;

void Init()
{
	SA::Debug::InitDefaultLogger();

	intf = new RHI::VkRenderInterface();
	// intf = new RHI::D12RenderInterface();

	intf->Create();

	// Device
	{
		auto infos = intf->QueryDeviceInfos();

		device = intf->CreateDevice(infos[0].get());
	}
}

void Uninit()
{
	intf->Destroy();
	delete intf;
}

int main()
{
	Init();



	Uninit();

	return 0;
}
