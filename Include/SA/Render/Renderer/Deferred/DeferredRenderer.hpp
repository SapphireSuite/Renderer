// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
#define SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD

#include <SA/Render/Renderer/Base/Renderer.hpp>

#include "DeferredSceneTextures.hpp"

namespace SA::RND
{
	class DeferredRenderer : public Renderer
	{
	protected:
	//{ Scene Textures

		SceneTextures* InstantiateSceneTexturesClass() override final;
		void DeleteSceneTexturesClass(SceneTextures* _sceneTextures) override final;

	//}


	//{ Frames

		void CreateWindowDependentFrameResources(const RendererSettings::RenderPassSettings& _settings, Frame& _frame, uint32_t _frameIndex) override final;
		void DestroyWindowDependentFrameResources(Frame& _frame) override final;

	//}
	};
}

#endif // SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
