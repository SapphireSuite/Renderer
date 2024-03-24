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
				auto& posRT = GBufferSubpass.AddAttachment(/*"GBuffer_Position", */dSceneTextures.gbuffer.position);

				// Deferred normal attachment.
				auto& normRT = GBufferSubpass.AddAttachment(/*"GBuffer_Normal", */dSceneTextures.gbuffer.normal);

				// Deferred base color attachment.
				auto& colorRT = GBufferSubpass.AddAttachment(/*"GBuffer_Color", */dSceneTextures.gbuffer.color);

				auto& metallicRoughnessRT = GBufferSubpass.AddAttachment(/*"GBuffer_MetallicRoughness", */dSceneTextures.gbuffer.metallicRoughness);

				auto& aoRT = GBufferSubpass.AddAttachment(/*"GBuffer_AO", */dSceneTextures.gbuffer.ao);

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
			RHI::RenderTargetDescriptor desc
			{
				.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
				.format = RHI::Format::R8G8B8A8_UNORM,
				.sampling = _settings.MSAA,
				.usage = static_cast<RHI::TextureUsage>(RHI::TextureUsageFlags::Color), // TODO: clean.
			};

			dSceneTextures.gbuffer.position = mContext->CreateRenderTarget(desc);
			dSceneTextures.gbuffer.normal = mContext->CreateRenderTarget(desc);

			dSceneTextures.gbuffer.color = mContext->CreateRenderTarget(desc);

			desc.format = RHI::Format::R8G8_UNORM;
			dSceneTextures.gbuffer.metallicRoughness = mContext->CreateRenderTarget(desc);

			desc.format = RHI::Format::R8_UNORM;
			dSceneTextures.gbuffer.ao = mContext->CreateRenderTarget(desc);
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
				mContext->DestroyRenderTarget(dSceneTextures.gbuffer.position);
				mContext->DestroyRenderTarget(dSceneTextures.gbuffer.normal);
				mContext->DestroyRenderTarget(dSceneTextures.gbuffer.color);
				mContext->DestroyRenderTarget(dSceneTextures.gbuffer.metallicRoughness);
				mContext->DestroyRenderTarget(dSceneTextures.gbuffer.ao);
			}
		}
	}

//}
}
