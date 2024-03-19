// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Forward/ForwardRenderer.hpp>

namespace SA::RND
{
//{ Scene Textures

	SceneTextures* ForwardRenderer::InstantiateSceneTexturesClass()
	{
		return new ForwardSceneTextures();
	}

	void ForwardRenderer::DeleteSceneTexturesClass(SceneTextures* _sceneTextures)
	{
		delete static_cast<ForwardSceneTextures*>(_sceneTextures);
	}

//}


//{ Frames

	void ForwardRenderer::CreateWindowDependentFrameResources(const RendererSettings::RenderPassSettings& _settings, Frame& _frame, uint32_t _frameIndex)
	{
		Renderer::CreateWindowDependentFrameResources(_settings, _frame, _frameIndex);

		// Scene Textures
		{
			ForwardSceneTextures& const fSceneTextures = *static_cast<ForwardSceneTextures*>(_frame.sceneTextures);

			// Colors
			{
				SA::RND::TextureDescriptor desc
				{
					.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
					.mipLevels = 1u,
					.format = mSwapchain ? mSwapchain->GetFormat() : Format::R8G8B8A8_SNORM,
					.sampling = _settings.MSAA,
					.usage = TextureUsage::RenderTarget,
				};

				if (_settings.MSAA != RHI:Sampling::S1Bit)
				{
					fSceneTextures.color.texture = mContext->CreateTexture(desc);

					if(mSwapchain)
						fSceneTextures.color.resolved = mContext->CreateTexture(mSwapchain, _frameIndex);
					else
						fSceneTextures.color.resolved = mContext->CreateTexture(desc);
				}
				else
				{
					if (mSwapchain)
						fSceneTextures.color.texture = mContext->CreateTexture(mSwapchain, _frameIndex);
					else
						fSceneTextures.color.texture = mContext->CreateTexture(desc);
				}
			}
		}
	}
	
	void ForwardRenderer::DestroyWindowDependentFrameResources(Frame& _frame)
	{
		Renderer::DestroyWindowDependentFrameResources(_frame);

		// Scene Textures
		{
			ForwardSceneTextures& const fSceneTextures = *static_cast<ForwardSceneTextures*>(_frame.sceneTextures);

			// Colors
			{
				mContext->DestroyTexture(fSceneTextures.color.texture);

				if(fSceneTextures.color.resolved)
					mContext->DestroyTexture(fSceneTextures.color.resolved);
			}
		}
	}

//}
}
