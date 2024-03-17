// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Forward/ForwardRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures& ForwardRenderer::GetSceneTextures()
	{
		return mSceneTextures;
	}

	void ForwardRenderer::CreateSceneTextures(const RendererSettings::RenderPassSettings& _settings)
	{
		Renderer::CreateSceneTextures(_settings);

		// Color
		{
			SA::RND::TextureDescriptor desc
			{
				.extents = mSwapchain->GetExtents(),
				.mipLevels = 1u,
				.format = mSwapchain->GetFormat(),
				.sampling = _settings.MSAA,
				.usage = TextureUsage::RenderTarget,
			};

			mSceneTextures.color = mContext->CreateTexture(desc);
		}
	}

	void ForwardRenderer::DestroySceneTextures()
	{
		Renderer::DestroySceneTextures();

		// Color
		{
			mContext->DestroyTexture(mSceneTextures.color);
		}
	}

//}

	void ForwardRenderer::MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo)
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
