// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_FRAMEBUFFER_GUARD

#include "Info/RHIRenderPassInfo.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class FrameBuffer;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class FrameBuffer;
	}

#endif

	namespace RHI
	{
		class Device;
		class RenderPass;

		class FrameBuffer
		{
		public:
			virtual ~FrameBuffer() = default;

			virtual void Create(const Device* _device, const RenderPass* _pass, const RenderPassInfo& _info) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::FrameBuffer& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual DX12::FrameBuffer& API_DirectX12();
			virtual const DX12::FrameBuffer& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_FRAMEBUFFER_GUARD
