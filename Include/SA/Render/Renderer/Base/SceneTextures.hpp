// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD
#define SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD

#include <SA/Render/RHI/Common/Texture/RHIRenderTarget.hpp>

namespace SA::RND
{
	struct SceneTextures
	{
		struct DepthTextures
		{
			RHI::RenderTarget* texture;
			RHI::RenderTarget* resolved;
		} depth;

		struct ColorTextures
		{
			RHI::RenderTarget* texture;
			RHI::RenderTarget* resolved;
		} color;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD
