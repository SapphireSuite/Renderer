// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD
#define SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD

#include <SA/Render/Renderer/Base/SceneTextures.hpp>

namespace SA::RND
{
	struct DeferredSceneTextures : public SceneTextures
	{
		struct GBufferTextures
		{
			RHI::RenderTarget* position;
			RHI::RenderTarget* normal;
			RHI::RenderTarget* color;
			RHI::RenderTarget* metallicRoughness;
			RHI::RenderTarget* ao;
		} gbuffer;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_DEFERRED_SCENE_TEXTURES_GUARD
