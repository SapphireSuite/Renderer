// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD

#include <SA/Render/LowLevel/Common/Device/RenderDeviceInfo.hpp>

#include "Queue/VkQueueMgrInfo.hpp"

namespace SA::VK
{
	class WindowSurface;
	struct QueueRequirements;

	struct DeviceInfo : public RenderDeviceInfo
	{
		friend class Device;

	//{ Physical Device

	public:
		/// Physical device handle.
		VkPhysicalDevice physicalDevice;
		VkPhysicalDeviceProperties physicalProperties{};

	private:
		/// Evaluate device to compute score.
		void Evaluate();

	//}

	//{ Extension
	
	public:
		/// \b Vulkan-only required extensions.
		std::vector<const char*> vkRequiredExts;

	private:
		bool CheckExtensionSupport() const noexcept;

	//}

	//{ Feature
	
	public:
		/// Physical device's supported features.
		VkPhysicalDeviceFeatures physicalFeatures{};
	
	private:
		bool CheckFeatureSupport(const VkPhysicalDeviceFeatures& _vkReqFeatures) const noexcept;
	
	//}
	

	//{ Queue Families

	public:
		QueueMgrInfo queueMgr;
		QueueMgrIndexInfo queueMgrIndex;

	private:
		int QueryQueueFamilies(const WindowSurface* _winSurface, QueueRequirements _queueReqs);

		void AddFamily(const WindowSurface* _winSurface,
			QueueRequirements& _queueReqs,
			const VkQueueFamilyProperties& _family,
			uint32_t _famIndex) noexcept;
	
		void EmplaceFamily(const VkQueueFamilyProperties& _vkFamily,
			QueueFamilyInfo& _famInfo,
			uint32_t& _reqNum,
			QueueFamilyIndexInfo& _famIndexInfo,
			uint32_t _famIndex,
			float _priority);

	//}
	};
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
