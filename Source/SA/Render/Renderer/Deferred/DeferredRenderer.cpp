// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Deferred/DeferredRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures* DeferredRenderer::InstantiateSceneTexturesClass()
	{
		return new DeferredSceneTextures();
	}

	void DeferredRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<DeferredSceneTextures*>(_sceneTextures);
	}

//}
}
