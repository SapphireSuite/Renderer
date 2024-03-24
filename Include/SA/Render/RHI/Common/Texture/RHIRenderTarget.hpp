// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_TARGET_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_TARGET_GUARD

#include "RHIITexture.hpp"
#include "RHIRenderTargetDescriptor.hpp"

namespace SA::RND::RHI
{
	class Device;
	class Swapchain;

	/**
	* \brief Texture used as render target for frame buffer attachment.
	*/
	class RenderTarget : public ITexture
	{
	public:
		virtual ~RenderTarget() = default;

		virtual void Create(const Device* _device, const RenderTargetDescriptor& _desc) = 0;
		virtual void CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex) = 0;
		virtual void Destroy(const Device* _device) = 0;
	};
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_TARGET_GUARD
