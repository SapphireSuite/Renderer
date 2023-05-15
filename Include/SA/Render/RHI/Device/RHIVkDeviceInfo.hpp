// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD

#include "RHIDeviceInfo.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Device/VkDeviceInfo.hpp>

namespace SA::RND::RHI
{
	class VkDeviceInfo : public RHI::DeviceInfo
	{
		SA::RND::VK::DeviceInfo mHandle;
		
	public:
		uint32_t GetScore() const override final;

		std::wstring GetName() const override final;

		uint32_t GetID() const override final;
		uint32_t GetVendorID() const override final;

		const VK::DeviceInfo* API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDE_RHI_VK_DEVICE_INFO_GUARD