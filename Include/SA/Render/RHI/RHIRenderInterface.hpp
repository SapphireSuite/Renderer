// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD

#include <vector>
#include <memory>
#include <forward_list>

#include "Device/RHIDevice.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Instance;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Factory;
	}

#endif

	namespace RHI
	{
		class RenderInterface
		{

		public:
			virtual ~RenderInterface() = default;

			virtual void Create() = 0;
			virtual void Destroy();

	//{ Device

		private:
			std::forward_list<Device*> mDevices;

		protected:
			virtual Device* InstantiateDeviceClass() const = 0;
			virtual void DeleteDeviceClass(Device* _device) const;

		public:
			Device* CreateDevice(const DeviceInfo* _info);
			void DestroyDevice(Device* _device);
			void DestroyAllDevices();

			virtual std::vector<std::shared_ptr<DeviceInfo>> QueryDeviceInfos() const = 0;

	//}

		public:
		#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			const VK::Instance* API_Vulkan() const;

		#endif

		#if SA_RENDER_LOWLEVEL_DX12_IMPL

			const DX12::Factory* API_DirectX12() const;

		#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD
