// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

// Must be include before to define 'VkResult'
#include <VulkanAPI.hpp>

#include <Debug/Exception_Vulkan.hpp>

namespace SA
{
	namespace VK
	{
		Exception_Vulkan::Exception_Vulkan(
			BaseInfo _info,
			VkResult _vkRes,
			std::wstring _predStr,
			std::wstring _details
		) noexcept :
			Exception(std::move(_info),
				_vkRes == VkResult::VK_SUCCESS,
				_predStr + L" must return VkResult::VK_SUCCESS",
				std::move(_details))
		{
		}
	}
}
