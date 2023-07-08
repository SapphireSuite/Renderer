// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD

#include "RHIPipelineLayout.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pipeline/VkPipelineLayout.hpp>

namespace SA::RND::RHI
{
	class VkPipelineLayout : public PipelineLayout
	{
		VK::PipelineLayout mHandle;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

		const VK::PipelineLayout& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD
