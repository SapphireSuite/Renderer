// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_SETTINGS_GUARD
#define SAPPHIRE_RENDER_RENDERER_SETTINGS_GUARD

#include <SA/Render/RHI/RHIRenderInterface.hpp>

namespace SA::RND
{
	struct RendererSettings
	{
		RHI::RenderInterface* intf = nullptr;
		RHI::IRenderWindow* window = nullptr;

		struct SwapchainSettings
		{
			/**
			* \brief buffering frame number.
			* Default is -1 (optimized by API).
			*/
			uint32_t bufferingCount = uint32_t(-1);

			///// Enable or disable VSync.
			//bool vSync = true;
		} swapchain;

		struct RenderPassSettings
		{
			RHI::Sampling MSAA = RHI::Sampling::S4Bits;

			/**
			* Custom extents
			* Default is -1 (use swapchain extents).
			*/
			Vec2ui extents = Vec2ui(-1);

			struct Depth
			{
				/// Whether to enable Depth.
				bool bEnabled = true;

				/// Generate Depth in a prepass. 
				bool bPrepass = true;

				/// Whether to use inverted depth.
				bool bInvertedDepth = true;

				/// Depth format.
				RHI::Format format = RHI::Format::D16_UNORM;
			} depth;
		} pass;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_SETTINGS_GUARD
