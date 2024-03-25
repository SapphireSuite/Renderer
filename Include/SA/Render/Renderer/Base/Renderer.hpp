// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_GUARD
#define SAPPHIRE_RENDER_RENDERER_GUARD

//#include <SA/Render/RHI/Context/RHIContext.hpp>

#include "RendererSettings.hpp"
#include "SceneTextures.hpp"

namespace SA::RND
{
	class Renderer
	{
	protected:
		RHI::RenderInterface* mInterface = nullptr;

	//{ Device

		RHI::Device* mDevice = nullptr;

		virtual RHI::DeviceRequirements GetDeviceRequirements() const;

		RHI::Context* mContext = nullptr;

	//}


	//{ Surface

		/**
		* \brief Window surface to render to.
		* Optionnal if IRenderWindow* is provided.
		*/
		RHI::WindowSurface* mWindowSurface = nullptr;

		/**
		* \brief Swapchain to render to.
		* Optionnal if IRenderWindow* is provided.
		*/
		RHI::Swapchain* mSwapchain = nullptr;

		void CreateWindowDependentResources(const RendererSettings& _settings);
		void DestroyWindowDependentResources(bool bResizeEvent = false);
		void ResizeWindowCallback();

	//}


		RHI::CommandPool* mCmdPool = nullptr;


	//{ Frames

		struct Frame
		{
			SceneTextures* sceneTextures = nullptr;
			RHI::FrameBuffer* frameBuffer = nullptr;
			
			RHI::CommandBuffer* cmdBuffer = nullptr;
		};

		std::vector<Frame> mFrames;

		RHI::RenderPass* mMainRenderPass = nullptr;

	//}


	//{ Scene Textures

		virtual SceneTextures* InstantiateSceneTexturesClass() = 0;
		virtual void DeleteSceneTexturesClass(SceneTextures* _sceneTextures) = 0;

		/**
		* Create Scene depth resources and add Depth-Only prepass if required.
		*/
		void CreateSceneDepthResourcesAndAddPrepass(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures);
		void DestroySceneDepthResources(SceneTextures* _sceneTextures);
		
		/**
		* Add or load scene depth attachment to subpass depending on settings `depth.bEnabled` and `depth.bPrepass`.
		*/
		void AddOrLoadSceneDepthAttachment(const RendererSettings::RenderPassSettings& _settings, RHI::SubpassInfo& _subpass, SceneTextures* _sceneTextures);

		void CreateSceneColorPresentResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex);
		void DestroySceneColorPresentResources(SceneTextures* _sceneTextures);

		virtual void CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex) = 0;
		virtual void DestroySceneTextureResources(SceneTextures* _sceneTextures) = 0;

	//}


	public:
		virtual void Create(const RendererSettings& _settings);
		virtual void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_GUARD
