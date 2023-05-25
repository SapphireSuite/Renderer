// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_RENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_RENDER_INTERFACE_GUARD

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include "RHIRenderInterface.hpp"

#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>

namespace SA::RND::RHI
{
	class VkRenderInterface : public RenderInterface
	{
		VK::Instance mInstance;

	public:
		void Create(const IWindowInterface* _winIntf) override final;
		void Destroy() override final;

//{ WindowSurface

	protected:
		WindowSurface* InstantiateWindowSurfaceClass() const override final;

//}


//{ Device

	protected:
		Device* InstantiateDeviceClass() const override final;

	public:
		std::vector<std::shared_ptr<DeviceInfo>> QueryDeviceInfos(const DeviceRequirements& _reqs) const override final;
//}


//{ Swapchain

	protected:
		Swapchain* InstantiateSwapchainClass() const override final;

//}

	public:
		const VK::Instance& API_Vulkan() const override final;

	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_RENDER_INTERFACE_GUARD
