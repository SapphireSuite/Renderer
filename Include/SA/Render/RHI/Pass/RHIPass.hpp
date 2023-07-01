// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_GUARD

#include "Info/RHIPassInfo.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class RenderPass;
	}

#endif

	namespace RHI
	{
		class Device;
		class CommandBuffer;
		class FrameBuffer;

		class Pass
		{
		protected:
			PassInfo mPassInfo;

		public:
			virtual ~Pass() = default;

			const PassInfo& GetInfo() const;

			virtual void Create(const Device* _device, PassInfo _info);
			virtual void Destroy(const Device* _device) = 0;

			virtual void Begin(const CommandBuffer* _cmd, const FrameBuffer* _fBuff) = 0;
			virtual void NextSubpass(const CommandBuffer* _cmd) = 0;
			virtual void End(const CommandBuffer* _cmd) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::RenderPass& API_Vulkan() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PASS_GUARD
