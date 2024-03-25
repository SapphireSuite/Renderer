// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Base/Renderer.hpp>

#include <SA/Render/RHI/Common/Device/RHIDevice.hpp>

namespace SA::RND
{
	void Renderer::Create(const RendererSettings& _settings)
	{
		mInterface = _settings.intf;

		if (_settings.window)
			mWindowSurface = mInterface->CreateWindowSurface(_settings.window);

		// Pickup device
		{
			RHI::DeviceRequirements reqs = GetDeviceRequirements();

			if(mWindowSurface)
				reqs.SetWindowSurface(mWindowSurface);

			auto infos = mInterface->QueryDeviceInfos(reqs);

			for (auto& info : infos)
				SA_LOG((L"Device found: Name: [%1], ID: [%2], Vendor [%3], Score [%4]", info->GetName(), info->GetID(), info->GetVendorID(), info->GetScore()), Normal, SA.Render.Renderer);
			
			// Select highest score device.
			mDevice = mInterface->CreateDevice(infos[0].get());
		}

		mContext = mDevice->CreateContext();

		mCmdPool = mContext->CreateCommandPool();

		CreateWindowDependentResources(_settings);
	}

	void Renderer::Destroy()
	{
		mDevice->WaitIdle();

		mInterface->DestroyDevice(mDevice);
		
		mDevice = nullptr;

		mInterface = nullptr;
	}

	RHI::DeviceRequirements Renderer::GetDeviceRequirements() const
	{
		return RHI::DeviceRequirements();
	}


//{ Surface

	void Renderer::CreateWindowDependentResources(const RendererSettings& _settings)
	{
		if (mWindowSurface)
		{
			RHI::SwapchainSettings swapchainSettings{};
			swapchainSettings.frameNum = _settings.swapchain.bufferingCount;

			mSwapchain = mInterface->CreateSwapchain(mDevice, mWindowSurface, swapchainSettings);
		}
		else
		{
			SA_ASSERT((NotEquals, _settings.swapchain.bufferingCount, uint32_t(-1)), L"Must provide valid bufferingCount parameters without mWindowSurface.");
			SA_ASSERT((NotEquals, _settings.pass.extents, Vec2ui(-1)), L"Must provide valid pass extents parameters without mWindowSurface.");
		}

		// Create frames
		{
			const uint32_t bufferingCount = mSwapchain ? mSwapchain->GetImageNum() : _settings.swapchain.bufferingCount;
			mFrames.resize(bufferingCount);

			for (uint32_t i = 0; i < bufferingCount; ++i)
			{
				auto& frame = mFrames[i];

				if(frame.cmdBuffer == nullptr)
					frame.cmdBuffer = mCmdPool->Allocate();

				if (frame.sceneTextures == nullptr)
					frame.sceneTextures = InstantiateSceneTexturesClass();

				RHI::RenderPassInfo MainPassInfo;
				CreateSceneTextureResources(_settings.pass, MainPassInfo, frame.sceneTextures, i);

				if (mMainRenderPass == nullptr) // Use same render pass for all frames: create only once.
				{
					mMainRenderPass = mContext->CreateRenderPass(MainPassInfo);
				}

				frame.frameBuffer = mContext->CreateFrameBuffer(mMainRenderPass, MainPassInfo);
			}
		}
	}
	
	void Renderer::DestroyWindowDependentResources(bool bResizeEvent)
	{
		// Destroy frames
		{
			for (auto& frame : mFrames)
			{
				mContext->DestroyFrameBuffer(frame.frameBuffer);
				DestroySceneTextureResources(frame.sceneTextures);

				if (!bResizeEvent)
				{
					mContext->DestroyRenderPass(mMainRenderPass);
					mMainRenderPass = nullptr;

					DeleteSceneTexturesClass(frame.sceneTextures);

					mCmdPool->Free(frame.cmdBuffer);
				}
			}

			if (!bResizeEvent)
				mFrames.clear();
		}

		if (mSwapchain)
		{
			mInterface->DestroySwapchain(mDevice, mSwapchain);
			mSwapchain = nullptr;
		}
	}

	void Renderer::ResizeWindowCallback()
	{
		DestroyWindowDependentResources(true);
		CreateWindowDependentResources(RendererSettings()); // TODO: Save Settings.
	}

//}


//{ Scene Textures

	void Renderer::CreateSceneDepthResourcesAndPass(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures)
	{
		if (_settings.depth.bEnabled)
		{
			RHI::TextureDescriptor desc
			{
				.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
				.format = _settings.depth.format,
				.sampling = _settings.MSAA,
				.usage = static_cast<RHI::TextureUsage>(RHI::TextureUsageFlags::Depth), // TODO: clean
				.clearColor = _settings.depth.bInvertedDepth ? Color{.r = 0.0f, .g = 0.0f } : Color{.r = 1.0f, .g = 0.0f }
			};

			_sceneTextures->depth.texture = mContext->CreateTexture(desc);
			_outPassInfo.RegisterRenderTarget(_sceneTextures->depth.texture, desc);

			if (_settings.MSAA != RHI::Sampling::S1Bit)
			{
				desc.sampling = RHI::Sampling::S1Bit;
				_sceneTextures->depth.resolved = mContext->CreateTexture(desc);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->depth.resolved, desc);
			}

			// Depth-Only Prepass
			if (_settings.depth.bPrepass)
			{
				RHI::SubpassInfo& depthPrepass = _outPassInfo.AddSubpass("Depth-Only Prepass");

				auto& depthRT = depthPrepass.AddAttachment(_sceneTextures->depth.texture, _sceneTextures->depth.resolved);
			}
		}
	}
	
	void Renderer::DestroySceneDepthResources(SceneTextures* _sceneTextures)
	{
		mContext->DestroyTexture(_sceneTextures->depth.texture);

		if (_sceneTextures->depth.resolved)
			mContext->DestroyTexture(_sceneTextures->depth.resolved);
	}

	void Renderer::AddOrLoadSceneDepthAttachment(const RendererSettings::RenderPassSettings& _settings, RHI::SubpassInfo& _subpass, SceneTextures* _sceneTextures)
	{
		if (_settings.depth.bEnabled)
		{
			// Used either as read only from prepass, or read write without depth prepass.
			auto& depthRT = _subpass.AddAttachment(_sceneTextures->depth.texture);

			if (_settings.depth.bPrepass)
				depthRT.loadMode = RHI::AttachmentLoadMode::Load;
		}
	}


	void Renderer::CreateSceneColorPresentResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex)
	{
		if (mSwapchain)
		{
			RHI::TextureDescriptor desc
			{
				.extents = mSwapchain->GetExtents(),
				.format = mSwapchain->GetFormat(),
				.sampling = RHI::Sampling::S1Bit, // Set later only for base texture.
				.usage = static_cast<RHI::TextureUsage>(RHI::TextureUsageFlags::Color), // TODO: clean.
				.clearColor = Color{ 0.0f, 0.0f, 0.15f, 1.0f }
			};

			if (_settings.MSAA != RHI::Sampling::S1Bit)
			{
				_sceneTextures->colorPresent.resolved = mContext->CreateTexture(mSwapchain, _frameIndex);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.resolved, desc);

				// Base texture
				desc.format = SRGBToUNORMFormat(mSwapchain->GetFormat());
				desc.sampling = _settings.MSAA;
				_sceneTextures->colorPresent.texture = mContext->CreateTexture(desc);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.texture, desc);
			}
			else
			{
				_sceneTextures->colorPresent.texture = mContext->CreateTexture(mSwapchain, _frameIndex);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.texture, desc);
			}
		}
		else
		{
			RHI::TextureDescriptor desc
			{
				.extents = _settings.extents,
				.format = RHI::Format::R8G8B8A8_UNORM,
				.sampling = RHI::Sampling::S1Bit, // Set later only for base texture.
				.usage = static_cast<RHI::TextureUsage>(RHI::TextureUsageFlags::Color), // TODO: clean.
				.clearColor = Color{ 0.0f, 0.0f, 0.15f, 1.0f }
			};

			if (_settings.MSAA != RHI::Sampling::S1Bit)
			{
				_sceneTextures->colorPresent.resolved = mContext->CreateTexture(desc);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.resolved, desc);

				// Base texture
				desc.format = SRGBToUNORMFormat(mSwapchain->GetFormat());
				desc.sampling = _settings.MSAA;
				_sceneTextures->colorPresent.texture = mContext->CreateTexture(desc);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.texture, desc);
			}
			else
			{
				_sceneTextures->colorPresent.texture = mContext->CreateTexture(desc);
				_outPassInfo.RegisterRenderTarget(_sceneTextures->colorPresent.texture, desc);
			}
		}
	}

	void Renderer::DestroySceneColorPresentResources(SceneTextures* _sceneTextures)
	{
		mContext->DestroyTexture(_sceneTextures->colorPresent.texture);

		if (_sceneTextures->colorPresent.resolved)
			mContext->DestroyTexture(_sceneTextures->colorPresent.resolved);
	}

//}
}
