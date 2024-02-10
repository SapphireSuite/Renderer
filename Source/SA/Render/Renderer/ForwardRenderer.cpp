// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <ForwardRenderer.hpp>

namespace SA::RND
{
	void ForwardRenderer::MakeRenderPassInfo(const RendererSettings::PassSettings& _settings, RHI::PassInfo& _passInfo)
	{
		const Vec2ui extents = GetRenderExtents(_settings);

		auto& mainSubpass = _passInfo.AddSubpass("Main");

		mainSubpass.sampling = _settings.MSAA;

		// Color and present attachment.
		auto& colorRT = mainSubpass.AddAttachment("Color");
		colorRT.format = mSwapchain ? mSwapchain->GetFormat() : RHI::Format::R8G8B8A8_SRGB;
		colorRT.usage = AttachmentUsage::Present;

		// Depth
		if (_settings.depth.bEnabled && !_settings.depth.bPrepass)
		{
			AddDepthAttachment(_settings, mainSubpass);
		}

		mainSubpass.SetAllAttachmentExtents(extents);
	}
}
