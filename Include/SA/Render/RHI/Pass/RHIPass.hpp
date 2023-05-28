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

		class Pass
		{
		protected:
			PassInfo mInfo;

		public:
			virtual ~Pass() = default;

			const PassInfo& GetInfo() const;

			virtual void Create(const Device* _device, PassInfo _info);
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::RenderPass& API_Vulkan() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PASS_GUARD
