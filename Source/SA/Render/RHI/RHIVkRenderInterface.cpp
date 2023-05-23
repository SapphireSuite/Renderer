// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIVkRenderInterface.hpp>

#include <Device/RHIVkDevice.hpp>
#include <Surface/RHIVkWindowSurface.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkRenderInterface::Create(IWindowInterface* _winIntf)
	{
		mInstance.Create(_winIntf->QueryRequiredExtensions());
	}
	
	void VkRenderInterface::Destroy()
	{
		RenderInterface::Destroy();

		mInstance.Destroy();
	}

//{ WindowSurface

	WindowSurface* VkRenderInterface::InstantiateWindowSurfaceClass() const
	{
		return new VkWindowSurface();
	}

	const VK::Instance& VkRenderInterface::API_Vulkan() const
	{
		return mInstance;
	}
	
//}


//{ Device

	Device* VkRenderInterface::InstantiateDeviceClass() const
	{
		return new VkDevice();
	}

	std::vector<std::shared_ptr<DeviceInfo>> VkRenderInterface::QueryDeviceInfos() const
	{
		std::vector<VK::DeviceInfo> vkInfos = mInstance.QueryDeviceInfos();

		std::vector<std::shared_ptr<DeviceInfo>> result;
		result.reserve(vkInfos.size());

		for(auto& vkInfo : vkInfos)
			result.emplace_back(new VkDeviceInfo(std::move(vkInfo)));

		return result;
	}

//}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL