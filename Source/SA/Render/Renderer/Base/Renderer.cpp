// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Base/Renderer.hpp>

#include <SA/Render/RHI/Device/RHIDevice.hpp>

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

				CreateSceneTextureResources(_settings.pass, frame.sceneTextures, i);
			}
		}
	}
	
	void Renderer::DestroyWindowDependentResources(bool bResizeEvent)
	{
		// Destroy frames
		{
			for (auto& frame : mFrames)
			{
				DestroySceneTextureResources(frame.sceneTextures);

				if (!bResizeEvent)
				{
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


//{ Frames

	void Renderer::CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, SceneTextures* _sceneTextures, uint32_t _frameIndex)
	{
		(void)_frameIndex;

		// Depth Textures
		{
			SA::RND::TextureDescriptor desc
			{
				.extents = mSwapchain ? mSwapchain->GetExtents() : _settings.extents,
				.mipLevels = 1u,
				.format = _settings.depth.format,
				.sampling = _settings.MSAA,
				.usage = TextureUsage::RenderTarget | TextureUsage::Depth,
			};

			if (_settings.depth.bPrepass)
				desc.usage |= TextureUsage::Input;

			_sceneTextures->depth.texture = mContext->CreateTexture(desc);

			if (_settings.MSAA != RHI::Sampling::S1Bit)
			{
				desc.sampling = RHI::Sampling::S1Bit;
				_sceneTextures->depth.resolved = mContext->CreateTexture(desc);
			}
		}
	}
	
	void Renderer::DestroySceneTextureResources(SceneTextures* _sceneTextures)
	{
		// Depth Textures
		{
			mContext->DestroyTexture(_sceneTextures->depth.texture);

			if (_sceneTextures->depth.resolved)
				mContext->DestroyTexture(_sceneTextures->depth.resolved);
		}
	}

//}
}
