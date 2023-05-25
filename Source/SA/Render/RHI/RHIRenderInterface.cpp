// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIRenderInterface.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	void RenderInterface::Destroy()
	{
		// DestroyAllSwapchains();
		DestroyAllDevices();
		DestroyAllWindowSurfaces();
	}

//{ WindowSurface

	void RenderInterface::DeleteWindowSurfaceClass(WindowSurface* _winSurface) const
	{
		SA_ASSERT((Nullptr, _winSurface), SA.Render.RHI);

		delete _winSurface;
	}

	WindowSurface* RenderInterface::CreateWindowSurface(const IRenderWindow* _window)
	{
		WindowSurface* const winSurface = mWindowSurfaces.emplace_front(InstantiateWindowSurfaceClass());

		SA_ASSERT((Nullptr, winSurface), SA.Render.RHI, (L"Window Surface instantiate class failed!"));

		winSurface->Create(this, _window);

		return winSurface;
	}

	void RenderInterface::DestroyWindowSurface(WindowSurface* _winSurface)
	{
		SA_ASSERT((Nullptr, _winSurface), SA.Render.RHI);

		if(std::erase(mWindowSurfaces, _winSurface))
		{
			_winSurface->Destroy(this);
			DeleteWindowSurfaceClass(_winSurface);
		}
		else
			SA_LOG((L"Try destroy Window Surface [%1] that does not belong to this context!", _winSurface), Error, SA.Render.RHI);
	}

	void RenderInterface::DestroyAllWindowSurfaces()
	{
		for(auto device : mWindowSurfaces)
		{
			device->Destroy(this);
			DeleteWindowSurfaceClass(device);
		}

		mWindowSurfaces.clear();
	}

//}


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
			SA_LOG((L"Try destroy Device [%1] that does not belong to this context!", _device), Error, SA.Render.RHI);
	}

	void RenderInterface::DestroyAllDevices()
	{
		for(auto device : mDevices)
		{
			device->Destroy();
			DeleteDeviceClass(device);
		}

		mDevices.clear();
	}

//}


//{ Swapchain

	void RenderInterface::DeleteSwapchainClass(Swapchain* _swapchain) const
	{
		SA_ASSERT((Nullptr, _swapchain), SA.Render.RHI);

		delete _swapchain;
	}

	Swapchain* RenderInterface::CreateSwapchain(const Device* _device,
		const WindowSurface* _winSurface,
		const SwapchainSettings& _settings)
	{
		Swapchain* const swapchain = mSwapchains.emplace_front(InstantiateSwapchainClass());

		SA_ASSERT((Nullptr, swapchain), SA.Render.RHI, (L"Swapchain instantiate class failed!"));

		swapchain->Create(this, _device, _winSurface, _settings);

		return swapchain;
	}

	void RenderInterface::DestroySwapchain(const Device* _device, Swapchain* _swapchain)
	{
		SA_ASSERT((Nullptr, _swapchain), SA.Render.RHI);

		if(std::erase(mSwapchains, _swapchain))
		{
			_swapchain->Destroy(this, _device);
			DeleteSwapchainClass(_swapchain);
		}
		else
			SA_LOG((L"Try destroy Swapchain [%1] that does not belong to this context!", _swapchain), Error, SA.Render.RHI);
	}

	// void RenderInterface::DestroyAllSwapchains()
	// {
	// 	for(auto swapchain : mSwapchains)
	// 	{
	// 		swapchain->Destroy();
	// 		DeleteSwapchainClass(swapchain);
	// 	}

	// 	mSwapchains.clear();
	// }

//}


#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Instance& RenderInterface::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Factory& RenderInterface::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
