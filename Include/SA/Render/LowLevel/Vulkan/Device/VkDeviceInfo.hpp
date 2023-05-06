// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD

#include <SA/Render/LowLevel/Common/Device/RenderDeviceInfo.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

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
		struct QueueMgrInfo
		{
			struct FamilyInfo
			{
				struct QueueInfo
				{
					uint32_t familyIndex = 0;
					uint32_t queueIndex = 0;
				};

				std::vector<QueueInfo> queues;
			};

			FamilyInfo graphics;
			FamilyInfo compute;
			FamilyInfo transfer;
			FamilyInfo present;


			struct IndexInfo
			{
				uint32_t index = ~uint32_t();
				uint32_t num = 0u;
				
				std::vector<float> queuePriorities;
			};

			std::vector<IndexInfo> indexInfos;
		} queueMgr;

	private:
		int QueryQueueFamilies(const WindowSurface* _winSurface, QueueRequirements _queueReqs) noexcept;

		void AddFamily(const WindowSurface* _winSurface,
			QueueRequirements& _queueReqs,
			const VkQueueFamilyProperties& _family,
			uint32_t _famIndex) noexcept;
	
		void EmplaceFamily(const VkQueueFamilyProperties& _vkFamily,
			QueueMgrInfo::FamilyInfo& _famInfo,
			uint32_t& _reqNum,
			QueueMgrInfo::IndexInfo& _currInfo,
			uint32_t _famIndex,
			float _priority);

		std::vector<VkDeviceQueueCreateInfo> GetQueueCreateInfos() const;

	//}
	};
}

#endif // SAPPHIRE_RENDER_VK_DEVICE_INFO_GUARD
