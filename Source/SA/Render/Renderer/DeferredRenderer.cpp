// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <DeferredRenderer.hpp>

namespace SA::RND
{
	void DeferredRenderer::MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo)
	{
		const Vec2ui extents = GetRenderExtents(_settings);
		
		_passInfo.subpasses.reserve(2u);

		// GBuffer
		{
			auto& GBufferSubpass = _passInfo.AddSubpass("GBuffer Pass");

			GBufferSubpass.sampling = _settings.MSAA;

			// Render Targets
			{
				// Deferred position attachment.
				auto& posRT = GBufferSubpass.AddAttachment("GBuffer_Position");

				// Deferred normal attachment.
				auto& normRT = GBufferSubpass.AddAttachment("GBuffer_Normal");

				// Deferred base color attachment.
				auto& colorRT = GBufferSubpass.AddAttachment("GBuffer_Color");

				// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
				auto& pbrRT = GBufferSubpass.AddAttachment("GBuffer_PBR");

				// Depth
				if (_settings.depth.bEnabled && !_settings.depth.bPrepass)
				{
					AddDepthAttachment(_settings, GBufferSubpass);
				}
			}

			GBufferSubpass.SetAllAttachmentExtents(extents);
		}

		// Present Subpass
		{
			auto& presentSubpass = _passInfo.AddSubpass("Present Pass");

			presentSubpass.sampling = _settings.MSAA;

			auto& presentRT = presentSubpass.AddAttachment("Color");
			presentRT.format = mSwapchain ? mSwapchain->GetFormat() : RHI::Format::R8G8B8A8_SRGB;
			presentRT.usage = AttachmentUsage::Present;

			presentSubpass.SetAllAttachmentExtents(extents);
		}
	}
}
