// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_VK_RENDER_PASS_GUARD

#include <SA/Render/RHI/Common/Pass/RHIRenderPass.hpp>

#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>

namespace SA::RND::RHI
{
	class VkRenderPass : public RenderPass
	{
		VK::RenderPass mHandle;

	public:
		void Create(const Device* _device, RenderPassInfo _info) override final;
		void Destroy(const Device* _device) override final;

		void Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff) override final;
		void NextSubpass(const CommandBuffer* _cmd) override final;
		void End(const CommandBuffer* _cmd) override final;

		const VK::RenderPass& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_RENDER_PASS_GUARD
