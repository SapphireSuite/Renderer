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

		if (mWindowSurface)
		{
			RHI::SwapchainSettings swapchainSettings{};
			swapchainSettings.frameNum = _settings.swapchain.bufferingCount,

			mSwapchain = mInterface->CreateSwapchain(mDevice, mWindowSurface, swapchainSettings);
		}

		const uint32_t bufferingCount = mSwapchain ? mSwapchain->GetImageNum() : _settings.swapchain.bufferingCount;

		SA_ASSERT((NotEquals, bufferingCount, uint32_t(-1)), L"Must provide valid bufferingCount parameters without mWindowSurface.");

		mContext = mDevice->CreateContext();

		CreateSceneTextures(_settings.pass);
		CreateRenderPass(_settings.pass);
		
		mFrameBuffers.resize(mSwapchain ? mSwapchain->GetImageNum() : _settings.swapchain.bufferingCount);
		for (uint32_t i = 0; i < mFrameBuffers.size(); ++i)
			mFrameBuffers[i] = mContext->CreateFrameBuffer(mMainPass, mSwapchain ? mSwapchain->GetBackBufferHandle(i) : nullptr);

		mCmdPool = mContext->CreateCommandPool();
		mCmdBuffers = mCmdPool->Allocate(mSwapchain ? mSwapchain->GetImageNum() : _settings.swapchain.bufferingCount);
	}

	void Renderer::Destroy()
	{
		mDevice->WaitIdle();

		DestroyRenderPass();

		mInterface->DestroyDevice(mDevice);
		
		mDevice = nullptr;

		mInterface = nullptr;
	}

	RHI::DeviceRequirements Renderer::GetDeviceRequirements() const
	{
		return RHI::DeviceRequirements();
	}

//{ Scene Textures

	void Renderer::CreateSceneTextures(const RendererSettings::RenderPassSettings& _settings)
	{
		SceneTextures& sceneTextures = GetSceneTextures();

		// Depth
		{
			SA::RND::TextureDescriptor desc
			{
				.extents = mSwapchain->GetExtents(),
				.mipLevels = 1u,
				.format = _settings.depth.format,
				.sampling = _settings.MSAA,
				.usage = TextureUsage::RenderTarget | TextureUsage::Depth,
			};

			if(_settings.depth.bPrepass)
				desc.usage |= TextureUsage::Input;

			sceneTextures.depth.texture = mContext->CreateTexture(desc);

			if (_settings.MSAA != RHI::Sampling::S1Bit)
			{
				desc.sampling = Sampling::S1Bit;
				sceneTextures.depth.resolved = mContext->CreateTexture(desc);
			}
		}
	}
	
	void Renderer::DestroySceneTextures()
	{
		SceneTextures& sceneTextures = GetSceneTextures();

		mContext->DestroyTexture(sceneTextures.depth.texture);

		if (sceneTextures.depth.resolved)
			mContext->DestroyTexture(sceneTextures.depth.resolved);
	}

//}

//{ RenderPass

	Vec2ui Renderer::GetRenderExtents(const RendererSettings::RenderPassSettings& _settings) const
	{
		if (_settings.extents != Vec2ui(-1))
			return _settings.extents;

		SA_ASSERT((Default, mSwapchain), SA.Render.Renderer, L"Must provide valid render extents without swapchain!");

		return mSwapchain->GetExtents();
	}

	void Renderer::MakeRenderPassInfo(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _passInfo)
	{
		const Vec2ui extents = GetRenderExtents(_settings);

		if (_settings.depth.bEnabled && _settings.depth.bPrepass)
		{
			auto& depthPass = _passInfo.AddSubpass("Depth-Only Prepass");
			depthPass.sampling = _settings.MSAA;

			AddDepthAttachment(_settings, depthPass);

			depthPass.SetAllAttachmentExtents(extents);
		}
	}
	
	void Renderer::AddDepthAttachment(const RendererSettings::RenderPassSettings& _settings, RHI::SubpassInfo& _subpassInfo)
	{
		auto& depthRT = _subpassInfo.AddAttachment("Depth");
		depthRT.format = _settings.depth.format;
		depthRT.type = AttachmentType::Depth;
		depthRT.usage = AttachmentUsage::InputNext;

		if (_settings.depth.bInvertedDepth)
		{
			depthRT.clearColor = Color::black;
		}
		else
		{
			depthRT.clearColor = Color::white;
		}
	}

	void Renderer::CreateRenderPass(const RendererSettings::RenderPassSettings& _settings)
	{
		RHI::RenderPassInfo passInfo;
		MakeRenderPassInfo(_settings, passInfo);

		mMainPass = mContext->CreateRenderPass(passInfo);
	}

	void Renderer::DestroyRenderPass()
	{
		mContext->DestroyRenderPass(mMainPass);
		mMainPass = nullptr;
	}

//}
}
