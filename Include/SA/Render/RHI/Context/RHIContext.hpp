// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_CONTEXT_GUARD

#include <forward_list>

#include <SA/Render/RHI/Pass/RHIPass.hpp>
#include <SA/Render/RHI/Pass/RHIFrameBuffer.hpp>
#include <SA/Render/RHI/Surface/RHID12Swapchain.hpp>

namespace SA::RND::RHI
{
	class Device;

	class Context
	{
		Device* mDevice = nullptr;

	public:
		virtual ~Context() = default;

		void Create(Device* _device);
		void Destroy();

//{ Pass

	private:
		std::forward_list<Pass*> mPasses;

	protected:
		virtual Pass* InstantiatePassClass() = 0;
		virtual void DeletePassClass(Pass* _pass);

	public:
		Pass* CreatePass(PassInfo _info);
		void DestroyPass(Pass* _pass);
		void DestroyAllPasses();

//}

//{ FrameBuffer

	private:
		std::forward_list<FrameBuffer*> mFrameBuffers;

	protected:
		virtual FrameBuffer* InstantiateFrameBufferClass() = 0;
		virtual void DeleteFrameBufferClass(FrameBuffer* _frameBuffer);

	public:
		FrameBuffer* CreateFrameBuffer(const Pass* _pass, std::shared_ptr<Swapchain::BackBufferHandle> _img = nullptr);
		void DestroyFrameBuffer(FrameBuffer* _frameBuffer);
		void DestroyAllFrameBuffers();

//}

	};
}

#endif // SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
