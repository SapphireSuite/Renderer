// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
#define SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD

#include "Renderer.hpp"

namespace SA::RND
{
	class DeferredRenderer : public Renderer
	{
	protected:
		void MakeRenderPassInfo(const RendererSettings::PassSettings& _settings, RHI::PassInfo& _passInfo) override final;
	};
}

#endif // SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
