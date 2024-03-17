// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Deferred/DeferredRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures& DeferredRenderer::GetSceneTextures()
	{
		return mSceneTextures;
	}

	void DeferredRenderer::CreateSceneTextures(const RendererSettings::RenderPassSettings& _settings)
	{
		Renderer::CreateSceneTextures(_settings);

		// GBuffer
		{
			SA::RND::TextureDescriptor desc
			{
				.extents = mSwapchain->GetExtents(),
				.mipLevels = 1u,
				.format = Format::R8G8B8A8_UNORM,
				.sampling = _settings.MSAA,
				.usage = TextureUsage::RenderTarget,
			};

			mSceneTextures.gbuffer.position = mContext->CreateTexture(desc);
			mSceneTextures.gbuffer.normal = mContext->CreateTexture(desc);

			desc.format = mSwapchain->GetFormat();
			mSceneTextures.gbuffer.color = mContext->CreateTexture(desc);

			desc.format = Format::R8G8_UNORM;
			mSceneTextures.gbuffer.metallicRoughness = mContext->CreateTexture(desc);

			desc.format = Format::R8_UNORM;
			mSceneTextures.gbuffer.ao = mContext->CreateTexture(desc);
		}
	}
	
	void DeferredRenderer::DestroySceneTextures()
	{
		Renderer::DestroySceneTextures();

		// GBuffer
		{
			mContext->DestroyTexture(mSceneTextures.gbuffer.position);
			mContext->DestroyTexture(mSceneTextures.gbuffer.normal);
			mContext->DestroyTexture(mSceneTextures.gbuffer.color);
			mContext->DestroyTexture(mSceneTextures.gbuffer.metallicRoughness);
			mContext->DestroyTexture(mSceneTextures.gbuffer.ao);
		}
	}

//}


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
