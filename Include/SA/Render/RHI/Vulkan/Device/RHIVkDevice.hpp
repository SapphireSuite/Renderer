// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD

#include <SA/Render/RHI/Common/Device/RHIDevice.hpp>

#include "RHIVkDeviceInfo.hpp"

#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>

namespace SA::RND::RHI
{
	class VkDevice : public Device
	{
		VK::Device mHandle;

	protected:
		Context* InstantiateContextClass() override final;

	public:
		void Create(const DeviceInfo* _info) override final;
		void Destroy() override final;

		void WaitIdle() override final;

		const VK::Device& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_DEVICE_GUARD
