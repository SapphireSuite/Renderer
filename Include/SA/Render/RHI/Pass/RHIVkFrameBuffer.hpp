// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD

#include "RHIFrameBuffer.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pass/VkFrameBuffer.hpp>

namespace SA::RND::RHI
{
	class VkFrameBuffer : public FrameBuffer
	{
		VK::FrameBuffer mHandle;

	public:
		void Create(const Device* _device, const RenderPass* _pass,
			std::shared_ptr<Swapchain::BackBufferHandle> _img) override final;
		void Destroy(const Device* _device) override final;

		const VK::FrameBuffer& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD
