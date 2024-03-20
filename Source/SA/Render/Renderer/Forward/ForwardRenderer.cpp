// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Forward/ForwardRenderer.hpp>

namespace SA::RND
{
//{ RenderPass

	void ForwardRenderer::FillRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, RHI::RenderPassInfo& _passInfo)
	{
		ForwardSceneTextures& fSceneTextures = *static_cast<ForwardSceneTextures*>(_sceneTextures);

		// Depth-Only prepass
		if (_settings.depth.bEnabled && _settings.depth.bPrepass)
		{
			auto& depthPass = _passInfo.AddSubpass("Depth-Only Prepass");

			AddDepthAttachment(_settings, _sceneTextures, depthPass);
		}


		// Present pass
		{
			auto& presentSubpass = AddPresentSubpass(_settings, _sceneTextures, _passInfo);

			if (_settings.depth.bEnabled && !_settings.depth.bPrepass)
			{
				AddDepthAttachment(_settings, _sceneTextures, presentSubpass);
			}
		}
	}

//}


//{ Scene Textures

	SceneTextures* ForwardRenderer::InstantiateSceneTexturesClass()
	{
		return new ForwardSceneTextures();
	}

	void ForwardRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<ForwardSceneTextures*>(_sceneTextures);
	}

//}
}
