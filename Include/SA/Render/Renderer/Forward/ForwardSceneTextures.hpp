// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_FORWARD_SCENE_TEXTURES_GUARD
#define SAPPHIRE_RENDER_RENDERER_FORWARD_SCENE_TEXTURES_GUARD

#include <SA/Render/Renderer/Base/SceneTextures.hpp>

namespace SA::RND
{
	struct ForwardSceneTextures : public SceneTextures
	{
		RHI::Texture* color;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_FORWARD_SCENE_TEXTURES_GUARD
