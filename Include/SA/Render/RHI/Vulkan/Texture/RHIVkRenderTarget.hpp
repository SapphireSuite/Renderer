// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_RENDER_TARGET_GUARD
#define SAPPHIRE_RENDER_RHI_VK_RENDER_TARGET_GUARD

#include <SA/Render/RHI/Common/Texture/RHIRenderTarget.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::RHI
{
	class VkRenderTarget : public RenderTarget
	{
		VK::Texture mHandle;

	public:
		void Create(const Device* _device, const RenderTargetDescriptor& _desc) override final;
		void CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex) override final;
		void Destroy(const Device* _device) override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_RENDER_TARGET_GUARD
