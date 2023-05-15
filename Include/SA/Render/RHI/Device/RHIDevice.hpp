// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DEVICE_GUARD
#define SAPPHIRE_RENDER_RHI_DEVICE_GUARD

#include "RHIDeviceInfo.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Device;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Device;
	}

#endif

	namespace RHI
	{
		class Device
		{
		public:
			virtual ~Device() = default;

			virtual void Create(const DeviceInfo* _info) = 0;
			virtual void Destroy() = 0;

		#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::Device* API_Vulkan() const;

		#endif

		#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::Device* API_DirectX12() const;

		#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_DEVICE_GUARD
