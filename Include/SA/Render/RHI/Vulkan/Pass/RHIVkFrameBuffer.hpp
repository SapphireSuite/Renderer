// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD

#include <SA/Render/RHI/Common/Pass/RHIFrameBuffer.hpp>

#include <SA/Render/LowLevel/Vulkan/Pass/VkFrameBuffer.hpp>

namespace SA::RND::RHI
{
	class VkFrameBuffer : public FrameBuffer
	{
		VK::FrameBuffer mHandle;

	public:
		void Create(const Device* _device, const RenderPass* _pass) override final;
		void Destroy(const Device* _device) override final;

		const VK::FrameBuffer& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_FRAMEBUFFER_GUARD
