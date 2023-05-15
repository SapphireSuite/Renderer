// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIRenderInterface.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	void RenderInterface::Destroy()
	{
		DestroyAllDevice();
	}

//{ Device

	void RenderInterface::DeleteDeviceClass(Device* _device) const
	{
		SA_ASSERT((Nullptr, _device), SA.Render.RHI);

		delete _device;
	}

	Device* RenderInterface::CreateDevice(const DeviceInfo* _info)
	{
		Device* const device = mDevices.emplace_front(InstantiateDeviceClass());

		SA_ASSERT((Nullptr, device), SA.Render.RHI, (L"Device instantiate class failed!"));

		device->Create(_info);

		return device;
	}

	void RenderInterface::DestroyDevice(Device* _device)
	{
		SA_ASSERT((Nullptr, _device), SA.Render.RHI);

		if(std::erase(mDevices, _device))
		{
			_device->Destroy();
			DeleteDeviceClass(_device);
		}
		else
			SA_LOG("Try destroy Device [%1] that does not belong to this context!", Error, SA.Render.RHI);
	}

	void RenderInterface::DestroyAllDevice()
	{
		for(auto device : mDevices)
		{
			device->Destroy();
			DeleteDeviceClass(device);
		}

		mDevices.clear();
	}

//}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Instance* RenderInterface::API_Vulkan() const
	{
		SA_ASSERT((Default, false), SA.Render.RHI.Vulkan, L"Query Vulkan API handle from non-vulkan object!");

		return nullptr;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Factory* RenderInterface::API_DirectX12() const
	{
		SA_ASSERT((Default, false), SA.Render.RHI.DX12, L"Query DirectX12 API handle from non-dx12 object!");

		return nullptr;
	}

#endif
}