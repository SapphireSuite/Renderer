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

//}
}
