// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD

#include "RHIDevice.hpp"
#include "RHIVkDeviceInfo.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>

namespace SA::RND::RHI
{
	class VkDevice : public Device
	{
		VK::Device mHandle;

	public:
		void Create(const DeviceInfo* _info) override final;
		void Destroy() override final;

		const VK::Device* API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD
