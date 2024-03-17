// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD
#define SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD

#include <SA/Render/Renderer/Base/Renderer.hpp>

#include "ForwardSceneTextures.hpp"

namespace SA::RND
{
	class ForwardRenderer : public Renderer
	{
	protected:
	//{ Scene Textures

		ForwardSceneTextures mSceneTextures;

		SceneTextures& GetSceneTextures() override final;

		void CreateSceneTextures(const RendererSettings::RenderPassSettings& _settings) override final;
		void DestroySceneTextures() override final;

	//}

		void MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo) override final;
	};
}

#endif // SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD
