// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_RHI_VK_SWAPCHAIN_GUARD

#include "RHISwapchain.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Surface/VkSwapchain.hpp>

namespace SA::RND::RHI
{
	class VkSwapchain : public Swapchain
	{
		VK::Swapchain mHandle;

		const VK::Device* mDevice = nullptr;

	public:
		void Create(const RenderInterface* _renderIntf,
			const Device* _device,
			const WindowSurface* _winSurface,
			const SwapchainSettings& _settings) override final;
		void Destroy(const RenderInterface* _renderIntf, const Device* _device) override final;

		Format GetFormat() const override final;
		uint32_t GetImageNum() const override final;
		const Vec2ui& GetExtents() const override final;

		uint32_t Begin() override final;
		void End(std::vector<CommandBuffer*> _cmds) override final;

		const VK::Swapchain& API_Vulkan() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL

#endif // SAPPHIRE_RENDER_RHI_VK_SWAPCHAIN_GUARD
