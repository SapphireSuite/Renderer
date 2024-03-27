// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_PASS_GUARD

#include "Info/RHIRenderPassInfo.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class RenderPass;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class RenderPass;
	}

#endif

	namespace RHI
	{
		class Device;
		class CommandBuffer;
		class FrameBuffer;

		class RenderPass
		{
		public:
			virtual ~RenderPass() = default;

			virtual void Create(const Device* _device, const RenderPassInfo& _info) = 0;
			virtual void Destroy(const Device* _device) = 0;

			virtual void Begin(const CommandBuffer* _cmd, FrameBuffer* _fBuff) = 0;
			virtual void NextSubpass(const CommandBuffer* _cmd) = 0;
			virtual void End(const CommandBuffer* _cmd) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::RenderPass& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::RenderPass& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_PASS_GUARD
