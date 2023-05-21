// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DEVICE_GUARD
#define SAPPHIRE_RENDER_RHI_DEVICE_GUARD

#include <forward_list>

#include <SA/Render/RHI/Context/RHIContext.hpp>

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
			virtual ~Device() = 0;

			virtual void Create(const DeviceInfo* _info) = 0;
			virtual void Destroy();

//{ Context

		private:
			std::forward_list<Context*> mContexts;

		protected:
			virtual Context* InstantiateContextClass() = 0;
			virtual void DeleteContextClass(Context* _context);

		public:
			Context* CreateContext();
			void DestroyContext(Context* _context);
			void DestroyAllContexts();

//}

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
