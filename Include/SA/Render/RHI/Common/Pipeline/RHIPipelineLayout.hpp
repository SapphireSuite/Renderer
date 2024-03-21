// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_LAYOUT_GUARD

#include "Descriptor/PipelineLayoutDescriptor.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class PipelineLayout;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class RootSignature;
	}

#endif

	namespace RHI
	{
		class Device;

		class PipelineLayout
		{
		public:
			virtual ~PipelineLayout() = default;

			virtual void Create(const Device* _device, const PipelineLayoutDescriptor& _desc) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::PipelineLayout& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::RootSignature& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_GUARD
