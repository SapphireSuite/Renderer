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
