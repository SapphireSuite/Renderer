// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <cstring>

#include <Device/VkDeviceInfo.hpp>
#include <Device/VkDeviceRequirements.hpp>
#include <Device/Queue/VkQueueRequirements.hpp>

#include <Surface/VkWindowSurface.hpp>

namespace SA::RND::VK
{
//{ Physical Device

	void DeviceInfo::Evaluate()
	{
		// Source: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families
	
	//{ Features score.

		const VkBool32* const bSuppFeatures = reinterpret_cast<const VkBool32*>(&physicalFeatures);
		constexpr size_t featureCount = sizeof(physicalFeatures) / sizeof(VkBool32);

		for(size_t i = 0; i < featureCount; ++i)
		{
			if(bSuppFeatures[i])
				score += 10;
		}
	//}

	//{ Properties score
	
		if(physicalProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 1000;

		// Maximum possible size of textures affects graphics quality
		score += physicalProperties.limits.maxImageDimension2D;

		// TODO: Implement more score based on properties.

	//}
	}

//}


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

		for(auto reqExt : vkRequiredExtensions)
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


//{ Queue Families

	int DeviceInfo::QueryQueueFamilies(const WindowSurface* _winSurface, QueueRequirements _queueReqs)
	{
		SA_ASSERT((Default, physicalDevice != VK_NULL_HANDLE), SA.Render.Vulkan, L"Query queue families of a null physical device!");
		SA_ASSERT((Default, !((_queueReqs.presentNum > 0) ^ (_winSurface != nullptr))),
			SA.Render.Vulkan, L"QueueType::Present requiere a valid RenderSurface as parameter!");

	//{ Query queue families
		uint32_t queueFamilyCount = 0;
		SA_VK_API(vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr));

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		SA_VK_API(vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data()));
	//}

		for(size_t i = 0u; i < queueFamilies.size() && !_queueReqs.IsEmpty(); ++i)
			AddFamily(_winSurface, _queueReqs, queueFamilies[i], i);


		return _queueReqs.GetCompletedCode();
	}

	void DeviceInfo::AddFamily(const WindowSurface* _winSurface,
		QueueRequirements& _queueReqs,
		const VkQueueFamilyProperties& _family,
		uint32_t _famIndex) noexcept
	{
		QueueFamilyIndexInfo info;
		info.index = _famIndex;

		// Graphics family.
		if (_queueReqs.graphicsNum > 0 && (_family.queueFlags & VK_QUEUE_GRAPHICS_BIT))
			EmplaceFamily(_family, queueMgr.graphics, _queueReqs.graphicsNum, info, _famIndex, 1.0f);


		// Compute family.
		if (_queueReqs.computeNum > 0 && (_family.queueFlags & VK_QUEUE_COMPUTE_BIT))
			EmplaceFamily(_family, queueMgr.compute, _queueReqs.computeNum, info, _famIndex, 1.0f);


		// Present family.
		if(_queueReqs.presentNum > 0)
		{
			VkBool32 presentSupport = false;
			SA_VK_API(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, _famIndex, *_winSurface, &presentSupport));

			if(presentSupport)
				EmplaceFamily(_family, queueMgr.present, _queueReqs.presentNum, info, _famIndex, 0.75f);
		}


		// Transfer family.
		if(_queueReqs.transferNum > 0 && (_family.queueFlags & VK_QUEUE_TRANSFER_BIT))
			EmplaceFamily(_family, queueMgr.transfer, _queueReqs.transferNum, info, _famIndex, 0.5f);


		if(info.num != 0)
			queueMgrIndex.familyInfos.push_back(info);
	}

	void DeviceInfo::EmplaceFamily(const VkQueueFamilyProperties& _vkFamily,
		QueueFamilyInfo& _famInfo,
		uint32_t& _reqNum,
		QueueFamilyIndexInfo& _famIndexInfo,
		uint32_t _famIndex,
		float _priority)
	{
			const uint32_t num = std::min(_reqNum, _vkFamily.queueCount - _famIndexInfo.num);

			for (uint32_t i = _famIndexInfo.num; i < _famIndexInfo.num + num; ++i)
			{
				_famIndexInfo.queuePriorities.push_back(_priority);
				_famInfo.queues.emplace_back(_famIndex, i);

				// Add score for each queue.
				score += 100;
			}

			_famIndexInfo.num += num;
			_reqNum -= num;
	}

//}
}
