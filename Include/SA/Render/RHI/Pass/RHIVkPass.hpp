// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_VK_PASS_GUARD

#include "RHIPass.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>

namespace SA::RND::RHI
{
	class VkPass : public Pass
	{
		VK::RenderPass mHandle;

	public:
		void Create(const Device* _device, PassInfo _info) override final;
		void Destroy(const Device* _device) override final;

		void Begin(const CommandBuffer* _cmd, const FrameBuffer* _fBuff) override final;
		void NextSubpass(const CommandBuffer* _cmd) override final;
		void End(const CommandBuffer* _cmd) override final;

		const VK::RenderPass& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_PASS_GUARD
