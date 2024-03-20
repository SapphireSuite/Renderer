// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Deferred/DeferredRenderer.hpp>

namespace SA::RND
{
//{ RenderPass

	void DeferredRenderer::FillRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, RHI::RenderPassInfo& _passInfo)
	{
		_passInfo.subpasses.reserve(3u);

		DeferredSceneTextures& dSceneTextures = *static_cast<DeferredSceneTextures*>(_sceneTextures);

		// Depth-Only prepass
		if (_settings.depth.bEnabled && _settings.depth.bPrepass)
		{
			auto& depthPass = _passInfo.AddSubpass("Depth-Only Prepass");

			AddDepthAttachment(_settings, _sceneTextures, depthPass);
		}

		// GBuffer
		{
			auto& GBufferSubpass = _passInfo.AddSubpass("GBuffer Pass");

			// Render Targets
			{
				// Deferred position attachment.
				auto& posRT = GBufferSubpass.AddAttachment("GBuffer_Position", dSceneTextures.gbuffer.position);

				// Deferred normal attachment.
				auto& normRT = GBufferSubpass.AddAttachment("GBuffer_Normal", dSceneTextures.gbuffer.normal);

				// Deferred base color attachment.
				auto& colorRT = GBufferSubpass.AddAttachment("GBuffer_Color", dSceneTextures.gbuffer.color);

				auto& metallicRoughnessRT = GBufferSubpass.AddAttachment("GBuffer_MetallicRoughness", dSceneTextures.gbuffer.metallicRoughness);

				auto& aoRT = GBufferSubpass.AddAttachment("GBuffer_AO", dSceneTextures.gbuffer.ao);

				// Depth
				if (_settings.depth.bEnabled && !_settings.depth.bPrepass)
				{
					AddDepthAttachment(_settings, _sceneTextures, GBufferSubpass);
				}
			}
		}

		// Present Subpass
		AddPresentSubpass(_settings, _sceneTextures, _passInfo);
	}

//}


//{ Scene Textures

	SceneTextures* DeferredRenderer::InstantiateSceneTexturesClass()
	{
		return new DeferredSceneTextures();
	}

	void DeferredRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<DeferredSceneTextures*>(_sceneTextures);
	}

	void DeferredRenderer::CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, uint32_t _frameIndex)
	{
		Renderer::CreateSceneTextureResources(_settings, _sceneTextures, _frameIndex);

		DeferredSceneTextures& dSceneTextures = *static_cast<DeferredSceneTextures*>(_sceneTextures);
			
		// GBuffer
		{
			SA::RND::TextureDescriptor desc
			{
				.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
				.mipLevels = 1u,
				.format = Format::R8G8B8A8_UNORM,
				.sampling = _settings.MSAA,
				.usage = TextureUsage::RenderTarget,
			};

			dSceneTextures.gbuffer.position = mContext->CreateTexture(desc);
			dSceneTextures.gbuffer.normal = mContext->CreateTexture(desc);

			dSceneTextures.gbuffer.color = mContext->CreateTexture(desc);

			desc.format = Format::R8G8_UNORM;
			dSceneTextures.gbuffer.metallicRoughness = mContext->CreateTexture(desc);

			desc.format = Format::R8_UNORM;
			dSceneTextures.gbuffer.ao = mContext->CreateTexture(desc);
		}
	}
	
	void DeferredRenderer::DestroySceneTextureResources(SceneTextures* _sceneTextures)
	{
		Renderer::DestroySceneTextureResources(_sceneTextures);

		// Scene Textures
		{
			DeferredSceneTextures& dSceneTextures = *static_cast<DeferredSceneTextures*>(_sceneTextures);

			// GBuffer
			{
				mContext->DestroyTexture(dSceneTextures.gbuffer.position);
				mContext->DestroyTexture(dSceneTextures.gbuffer.normal);
				mContext->DestroyTexture(dSceneTextures.gbuffer.color);
				mContext->DestroyTexture(dSceneTextures.gbuffer.metallicRoughness);
				mContext->DestroyTexture(dSceneTextures.gbuffer.ao);
			}
		}
	}

//}
}
