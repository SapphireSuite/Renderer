// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_GUARD
#define SAPPHIRE_RENDER_RENDERER_GUARD

//#include <SA/Render/RHI/Context/RHIContext.hpp>

#include "RendererSettings.hpp"

namespace SA::RND
{
	class Renderer
	{
	protected:
		RHI::RenderInterface* mInterface = nullptr;

		/**
		* \brief Window surface to render to.
		* Optionnal if IRenderWindow* is provided.
		*/
		RHI::WindowSurface* mWindowSurface = nullptr;

	//{ Device

		RHI::Device* mDevice = nullptr;

		virtual RHI::DeviceRequirements GetDeviceRequirements() const;

	//}

		/**
		* \brief Swapchain to render to.
		* Optionnal if IRenderWindow* is provided.
		*/
		RHI::Swapchain* mSwapchain = nullptr;


		RHI::Context* mContext = nullptr;


	//{ RenderPass
		
		RHI::RenderPass* mMainPass = nullptr;

		Vec2ui GetRenderExtents(const RendererSettings::RenderPassSettings& _settings) const;

		virtual void MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo);
		void AddDepthAttachment(const RendererSettings::RenderPassSettings& _settings, RHI::SubpassInfo& _subpassInfo);

		void CreateRenderPass(const RendererSettings::RenderPassSettings& _settings);
		void DestroyRenderPass();

	//}

		std::vector<RHI::FrameBuffer*> mFrameBuffers;
		
		RHI::CommandPool* mCmdPool = nullptr;
		std::vector<RHI::CommandBuffer*> mCmdBuffers;


	public:
		virtual void Create(const RendererSettings& _settings);
		virtual void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_GUARD
