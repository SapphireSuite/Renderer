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


		struct Frame
		{
			SceneTextures* sceneTextures = nullptr;
			RHI::FrameBuffer* frameBuffer = nullptr;
			
			RHI::CommandBuffer* cmdBuffer = nullptr;
		};

		std::vector<Frame> mFrames;


	//{ Scene Textures

		virtual SceneTextures* InstantiateSceneTexturesClass() = 0;
		virtual void DeleteSceneTexturesClass(SceneTextures* _sceneTextures) = 0;

	//}


	public:
		virtual void Create(const RendererSettings& _settings);
		virtual void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_GUARD
