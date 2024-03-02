// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD
#define SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD

#include <SA/Render/Renderer/Base/SceneTextures.hpp>

namespace SA::RND
{
	class DeferredSceneTextures : public SceneTextures
	{
		struct GBufferTextures
		{
			RHI::Texture* position;
			RHI::Texture* normal;
			RHI::Texture* color;
			RHI::Texture* metallicRoughness;
			RHI::Texture* ao;
		} gbuffer;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD
