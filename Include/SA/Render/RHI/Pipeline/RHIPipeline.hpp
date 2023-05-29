// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_GUARD

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Pipeline;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Pipeline;
	}

#endif

	namespace RHI
	{
		class Device;
		class Pass;

		class Pipeline
		{
		public:
			virtual void Create(const Device* _device, const Pass* _pass) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			const VK::Pipeline& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			const DX12::Pipeline& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_GUARD