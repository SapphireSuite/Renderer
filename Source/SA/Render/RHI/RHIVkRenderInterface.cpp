// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIVkRenderInterface.hpp>

#include <Device/RHIVkDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkRenderInterface::Create()
	{
		mInstance.Create();
	}
	
	void VkRenderInterface::Destroy()
	{
		RenderInterface::Destroy();

		mInstance.Destroy();
	}

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

	const VK::Instance* VkRenderInterface::API_Vulkan() const
	{
		return &mInstance;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL