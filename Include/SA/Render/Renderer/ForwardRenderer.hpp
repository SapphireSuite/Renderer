// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD
#define SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD

#include "Renderer.hpp"

namespace SA::RND
{
	class ForwardRenderer : public Renderer
	{
	protected:
		void MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo) override final;
	};
}

#endif // SAPPHIRE_RENDER_FORWARD_RENDERER_GUARD
