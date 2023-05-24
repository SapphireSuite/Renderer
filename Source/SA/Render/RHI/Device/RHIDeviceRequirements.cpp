// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIDeviceRequirements.hpp>

#include <Surface/RHIWindowSurface.hpp>

namespace SA::RND::RHI
{
	void DeviceRequirements::SetWindowSurface(const WindowSurface* _winSurface, bool bSetPresentQueue)
	{
		if (winSurface == _winSurface)
			return;

		winSurface = _winSurface;

		if (winSurface)
		{
			if (bSetPresentQueue)
				++queue.presentNum;
		}
		else
		{
			if (bSetPresentQueue)
				--queue.presentNum;
		}
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::DeviceRequirements DeviceRequirements::API_Vulkan() const
	{
		VK::DeviceRequirements vkDevReqs;

		vkDevReqs.queue = queue;

		if (winSurface)
			vkDevReqs.SetWindowSurface(&winSurface->API_Vulkan(), false); // @rmaxime: Present queue already added.

		return vkDevReqs;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::DeviceRequirements DeviceRequirements::API_DirectX12() const
	{
		DX12::DeviceRequirements d12DevReqs;

		d12DevReqs.queue = queue;

		return d12DevReqs;
	}

#endif
}
