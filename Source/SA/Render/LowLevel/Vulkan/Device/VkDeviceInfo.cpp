// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <cstring>

#include <Device/VkDeviceInfo.hpp>

namespace SA::VK
{
//{ Extension
	bool IsExtensionSupported(const std::vector<VkExtensionProperties>& _vkSupportedExts,
		const char* _vkExt) noexcept
	{
		for(const auto& suppExt : _vkSupportedExts)
		{
			// Extension found.
			if(std::strcmp(_vkExt, suppExt.extensionName) == 0)
				return true;
		}

		return false;
	}

	bool DeviceInfo::CheckExtensionSupport() const noexcept
	{
	//{ Query supported extensions.
		uint32_t extensionCount = 0u;
		SA_VK_API(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr),
			L"Failed to query physical graphic device extension properties count.");

		std::vector<VkExtensionProperties> vkSupportedExts(extensionCount);
		SA_VK_API(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, vkSupportedExts.data()),
			L"Failed to query physical graphic device extension properties.");
	//}

		for(auto reqExt : vkRequiredExts)
		{
			if(!IsExtensionSupported(vkSupportedExts, reqExt))
				return false;
		}

		return true;
	}

//}


//{ Feature

	bool DeviceInfo::CheckFeatureSupport(const VkPhysicalDeviceFeatures& _vkReqFeatures) const noexcept
	{
		const VkBool32* const bSuppFeatures = reinterpret_cast<const VkBool32*>(&physicalFeatures);
		const VkBool32* const bReqFeatures = reinterpret_cast<const VkBool32*>(&_vkReqFeatures);
		constexpr size_t count = sizeof(_vkReqFeatures) / sizeof(VkBool32);

		for(size_t i = 0u; i < count; ++i)
		{
			if(bReqFeatures[i])
			{
				if(!bSuppFeatures[i])
					return false;
			}
		}

		return true;
	}

//}


	void DeviceInfo::Evaluate()
	{
		// TODO: Implement score: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families
	}
}
