// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD

#include <SA/Render/RHI/Common/Pipeline/RHIPipelineLayout.hpp>

#include <SA/Render/LowLevel/Vulkan/Pipeline/VkPipelineLayout.hpp>

namespace SA::RND::RHI
{
	class VkPipelineLayout : public PipelineLayout
	{
		VK::PipelineLayout mHandle;

	public:
		void Create(const Device* _device, const PipelineLayoutDescriptor& _desc) override final;
		void Destroy(const Device* _device) override final;

		const VK::PipelineLayout& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_PIPELINE_LAYOUT_GUARD
