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

	void DeferredRenderer::CreateWindowDependentFrameResources(const RendererSettings::RenderPassSettings& _settings, Frame& _frame, uint32_t _frameIndex)
	{
		Renderer::CreateWindowDependentFrameResources(_settings, _frame, _frameIndex);

		// Scene Textures
		{
			DeferredSceneTextures& const dSceneTextures = *static_cast<DeferredSceneTextures*>(_frame.sceneTextures);
			
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
	}
	
	void DeferredRenderer::DestroyWindowDependentFrameResources(Frame& _frame)
	{
		Renderer::DestroyWindowDependentFrameResources(_frame);

		// Scene Textures
		{
			DeferredSceneTextures& const dSceneTextures = *static_cast<DeferredSceneTextures*>(_frame.sceneTextures);

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
