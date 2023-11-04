// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_RHI_RESOURCE_INITIALIZER_GUARD

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	namespace VK
	{
		class ResourceInitializer;
	}
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	namespace DX12
	{
		class ResourceInitializer;
	}
#endif

	namespace RHI
	{
		class Device;

		class ResourceInitializer
		{
		protected:
			const Device* mDevice = nullptr;

		public:
			virtual ~ResourceInitializer() = default;

			virtual void Create(const Device* _device);
			virtual void Destroy();

			virtual void Submit() = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual VK::ResourceInitializer& API_Vulkan();

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual DX12::ResourceInitializer& API_DirectX12();

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_RESOURCE_INITIALIZER_GUARD
