// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD

#include <SA/Render/RHI/Common/Device/RHIDeviceInfo.hpp>

#include <SA/Render/LowLevel/Vulkan/Device/VkDeviceInfo.hpp>

namespace SA::RND::RHI
{
	class VkDeviceInfo : public RHI::DeviceInfo
	{
		VK::DeviceInfo mHandle;
		
	public:
		VkDeviceInfo() = default;
		VkDeviceInfo(VK::DeviceInfo&& _handle);

		uint32_t GetScore() const override final;

		std::wstring GetName() const override final;

		uint32_t GetID() const override final;
		uint32_t GetVendorID() const override final;

		const VK::DeviceInfo& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD
