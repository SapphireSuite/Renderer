// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Renderer.hpp>

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

//{ RenderPass

	Vec2ui Renderer::GetRenderExtents(const RendererSettings::PassSettings& _settings) const
	{
		if (_settings.extents != Vec2ui(-1))
			return _settings.extents;

		SA_ASSERT((Default, mSwapchain), SA.Render.Renderer, L"Must provide valid render extents without swapchain!");

		return mSwapchain->GetExtents();
	}

	void Renderer::MakeRenderPassInfo(const RendererSettings::PassSettings& _settings, RHI::PassInfo& _passInfo)
	{
		const Vec2ui extents = GetRenderExtents(_settings);

		if (_settings.depth.bEnabled && _settings.depth.bPrepass)
		{
			auto& depthPass = _passInfo.AddSubpass("Depth Prepass");
			depthPass.sampling = _settings.MSAA;
			depthPass.SetAllAttachmentExtents(extents);

			AddDepthAttachment(_settings, depthPass);
		}
	}
	
	void Renderer::AddDepthAttachment(const RendererSettings::PassSettings& _settings, RHI::SubpassInfo& _subpassInfo)
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

	void Renderer::CreateRenderPass(const RendererSettings::PassSettings& _settings)
	{
		RHI::PassInfo passInfo;
		MakeRenderPassInfo(_settings, passInfo);

		mMainPass = mContext->CreatePass(passInfo);
	}

	void Renderer::DestroyRenderPass()
	{
		mContext->DestroyPass(mMainPass);
		mMainPass = nullptr;
	}

//}
}
