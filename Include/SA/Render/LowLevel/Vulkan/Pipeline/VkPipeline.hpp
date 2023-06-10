// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_GUARD

#include "Info/VkGraphicsPipelineInfo.hpp"

namespace SA::RND::VK
{
	class Device;

	class Pipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const GraphicsPipelineInfo& _info);
		void Create(const Device& _device, const VkGraphicsPipelineCreateInfo& _vkInfo);
		void Destroy(const Device& _device);

		operator VkPipeline() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_PIPELINE_GUARD
