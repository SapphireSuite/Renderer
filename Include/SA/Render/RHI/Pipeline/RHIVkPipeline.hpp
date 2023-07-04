// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_PIPELINE_GUARD

#include "RHIPipeline.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pipeline/VkPipeline.hpp>

namespace SA::RND::RHI
{
	class VkPipeline : public Pipeline
	{
		VK::Pipeline mHandle;

	public:
		void Create(const Device* _device, const GraphicsPipelineInfo& _info) override final;
		void Destroy(const Device* _device) override final;

		void Bind(const CommandBuffer* _cmd) override final;

		const VK::Pipeline& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_PIPELINE_GUARD
