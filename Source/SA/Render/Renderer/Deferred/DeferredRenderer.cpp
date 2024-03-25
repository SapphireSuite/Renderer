// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Deferred/DeferredRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures* DeferredRenderer::InstantiateSceneTexturesClass()
	{
		return new DeferredSceneTextures();
	}

	void DeferredRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<DeferredSceneTextures*>(_sceneTextures);
	}


	void DeferredRenderer::CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex)
	{
		DeferredSceneTextures& dSceneTextures = *static_cast<DeferredSceneTextures*>(_sceneTextures);

		CreateSceneDepthResourcesAndPass(_settings, _outPassInfo, _sceneTextures);

		// GBuffer
		{
			auto& GBufferSubpass = _outPassInfo.AddSubpass("GBuffer Pass");

			RHI::TextureDescriptor desc
			{
				.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
				.format = RHI::Format::R8G8B8A8_UNORM,
				.sampling = _settings.MSAA,
				.usage = static_cast<RHI::TextureUsage>(RHI::TextureUsageFlags::Color), // TODO: clean.
			};

			// Deferred position attachment.
			dSceneTextures.gbuffer.position = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(dSceneTextures.gbuffer.position, desc);
			GBufferSubpass.AddAttachment(dSceneTextures.gbuffer.position);

			// Deferred normal attachment.
			dSceneTextures.gbuffer.normal = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(dSceneTextures.gbuffer.normal, desc);
			GBufferSubpass.AddAttachment(dSceneTextures.gbuffer.normal);

			// Deferred base color attachment.
			dSceneTextures.gbuffer.color = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(dSceneTextures.gbuffer.color, desc);
			GBufferSubpass.AddAttachment(dSceneTextures.gbuffer.color);

			desc.format = RHI::Format::R8G8_UNORM;
			dSceneTextures.gbuffer.metallicRoughness = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(dSceneTextures.gbuffer.metallicRoughness, desc);
			GBufferSubpass.AddAttachment(dSceneTextures.gbuffer.metallicRoughness);

			desc.format = RHI::Format::R8_UNORM;
			dSceneTextures.gbuffer.ao = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(dSceneTextures.gbuffer.ao, desc);
			GBufferSubpass.AddAttachment(dSceneTextures.gbuffer.ao);

			AddOrLoadSceneDepthAttachment(_settings, GBufferSubpass, _sceneTextures);
		}

		// Composition and present pass
		{
			CreateSceneColorPresentResources(_settings, _outPassInfo, _sceneTextures, _frameIndex);

			auto& colorPresentSubpass = _outPassInfo.AddSubpass("Composition Present Pass");

			colorPresentSubpass.AddAttachment(dSceneTextures.colorPresent.texture, dSceneTextures.colorPresent.resolved);
		}
	}
	
	void DeferredRenderer::DestroySceneTextureResources(SceneTextures* _sceneTextures)
	{
		DeferredSceneTextures& dSceneTextures = *static_cast<DeferredSceneTextures*>(_sceneTextures);

		DestroySceneDepthResources(_sceneTextures);

		// GBuffer
		{
			mContext->DestroyTexture(dSceneTextures.gbuffer.position);
			mContext->DestroyTexture(dSceneTextures.gbuffer.normal);
			mContext->DestroyTexture(dSceneTextures.gbuffer.color);
			mContext->DestroyTexture(dSceneTextures.gbuffer.metallicRoughness);
			mContext->DestroyTexture(dSceneTextures.gbuffer.ao);
		}

		DestroySceneColorPresentResources(_sceneTextures);
	}

//}
}
