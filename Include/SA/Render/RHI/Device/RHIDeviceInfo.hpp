// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_DEVICE_INFO_GUARD

#include <cstdint>
#include <string>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		struct DeviceInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		struct DeviceInfo;
	}
	
#endif

	namespace RHI
	{
		class DeviceInfo
		{
		public:
			virtual ~DeviceInfo() = default;

			virtual uint32_t GetScore() const = 0;
			
			virtual std::wstring GetName() const = 0;
			
			virtual uint32_t GetID() const = 0;
			virtual uint32_t GetVendorID() const = 0;

		#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::DeviceInfo* API_Vulkan() const;

		#endif

		#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::DeviceInfo* API_DirectX12() const;

		#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_DEVICE_INFO_GUARD
