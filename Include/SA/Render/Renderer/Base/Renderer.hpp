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

	//}


	//{ RenderPass

		RHI::RenderPass* mMainRenderPass = nullptr;

		void AddDepthAttachment(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, SubpassInfo& _subpassInfo);
		SubpassInfo& AddPresentSubpass(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, RHI::RenderPassInfo& _passInfo);
		virtual void FillRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, RHI::RenderPassInfo& _passInfo) = 0;

	//}


	//{ Scene Textures

		virtual SceneTextures* InstantiateSceneTexturesClass() = 0;
		virtual void DeleteSceneTexturesClass(SceneTextures* _sceneTextures) = 0;

		virtual void CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, uint32_t _frameIndex);
		virtual void DestroySceneTextureResources(SceneTextures* _sceneTextures);

	//}


	public:
		virtual void Create(const RendererSettings& _settings);
		virtual void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_GUARD
