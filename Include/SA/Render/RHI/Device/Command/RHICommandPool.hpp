// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_RHI_COMMAND_POOL_GUARD

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class CommandPool;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class CommandAllocator;
	}

#endif

	namespace RHI
	{
		class Device;

		class CommandPool
		{
		protected:
			const Device* mDevice = nullptr;

		public:
			virtual ~CommandPool() = default;

			virtual void Create(const Device* _device);
			virtual void Destroy(const Device* _device);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::CommandPool& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::CommandAllocator& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_COMMAND_POOL_GUARD
