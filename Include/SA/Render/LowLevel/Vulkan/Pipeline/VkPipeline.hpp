// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_GUARD

#include "Info/VkGraphicsPipelineInfo.hpp"

namespace SA::RND::VK
{
	class Device;
	class CommandBuffer;

	class Pipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;

		VkPipelineBindPoint mBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	public:
		void Create(const Device& _device, const GraphicsPipelineInfo& _info);
		void Create(const Device& _device, const VkGraphicsPipelineCreateInfo& _vkInfo);
		void Create(const Device& _device, const VkComputePipelineCreateInfo& _vkInfo);
		void Destroy(const Device& _device);

		void Bind(const CommandBuffer& _cmd);

		operator VkPipeline() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_PIPELINE_GUARD
