// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Forward/ForwardRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures* ForwardRenderer::InstantiateSceneTexturesClass()
	{
		return new ForwardSceneTextures();
	}

	void ForwardRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<ForwardSceneTextures*>(_sceneTextures);
	}


	void ForwardRenderer::CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex)
	{
		ForwardSceneTextures& fSceneTextures = *static_cast<ForwardSceneTextures*>(_sceneTextures);

		CreateSceneDepthResourcesAndAddPrepass(_settings, _outPassInfo, _sceneTextures);

		CreateSceneColorPresentResources(_settings, _outPassInfo, _sceneTextures, _frameIndex);

		// Scene Color Present Pass.
		{
			auto& colorPresentSubpass = _outPassInfo.AddSubpass("Color Present Pass");

			colorPresentSubpass.AddAttachment(fSceneTextures.colorPresent.texture, fSceneTextures.colorPresent.resolved);

			AddOrLoadSceneDepthAttachment(_settings, colorPresentSubpass, _sceneTextures);
		}
	}

	void ForwardRenderer::DestroySceneTextureResources(SceneTextures* _sceneTextures)
	{
		DestroySceneDepthResources(_sceneTextures);
		DestroySceneColorPresentResources(_sceneTextures);
	}

//}
}
