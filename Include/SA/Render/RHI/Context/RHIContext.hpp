// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_CONTEXT_GUARD

#include <forward_list>

#include <SA/Render/RHI/Pass/RHIPass.hpp>
#include <SA/Render/RHI/Pass/RHIFrameBuffer.hpp>
#include <SA/Render/RHI/Surface/RHISwapchain.hpp>
#include <SA/Render/RHI/Shader/RHIShader.hpp>
#include <SA/Render/RHI/Pipeline/RHIPipelineLayout.hpp>
#include <SA/Render/RHI/Pipeline/RHIPipeline.hpp>
#include <SA/Render/RHI/Pipeline/RHIRenderViews.hpp>
#include <SA/Render/RHI/Device/Command/RHICommandPool.hpp>
#include <SA/Render/RHI/Buffer/RHIBuffer.hpp>

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


//{ Shader

	private:
		std::forward_list<Shader*> mShaders;

	protected:
		virtual Shader* InstantiateShaderClass() = 0;
		virtual void DeleteShaderClass(Shader* _shader);

	public:
		Shader* CreateShader(const ShaderCompileResult& _comp);
		void DestroyShader(Shader* _shader);
		void DestroyAllShaders();

//}


//{ RenderViews

	private:
		std::forward_list<RenderViews*> mRenderViews;

	protected:
		virtual RenderViews* InstantiateRenderViewsClass() = 0;
		virtual void DeleteRenderViewsClass(RenderViews* _RenderViews);

	public:
		RenderViews* CreateRenderViews();
		void DestroyRenderViews(RenderViews* _RenderViews);
		void DestroyAllRenderViews();

//}


//{ PipelineLayout

	private:
		std::forward_list<PipelineLayout*> mPipelineLayouts;

	protected:
		virtual PipelineLayout* InstantiatePipelineLayoutClass() = 0;
		virtual void DeletePipelineLayoutClass(PipelineLayout* _pipLayout);

	public:
		PipelineLayout* CreatePipelineLayout();
		void DestroyPipelineLayout(PipelineLayout* _pipLayout);
		void DestroyAllPipelineLayouts();

//}


//{ Pipeline

	private:
		std::forward_list<Pipeline*> mPipelines;

	protected:
		virtual Pipeline* InstantiatePipelineClass() = 0;
		virtual void DeletePipelineClass(Pipeline* _pipeline);

	public:
		Pipeline* CreatePipeline(const GraphicsPipelineInfo& _info);
		void DestroyPipeline(Pipeline* _pipeline);
		void DestroyAllPipelines();

//}


//{ CommandPool

	private:
		std::forward_list<CommandPool*> mCommandPools;

	protected:
		virtual CommandPool* InstantiateCommandPoolClass() = 0;
		virtual void DeleteCommandPoolClass(CommandPool* _cmdPool);

	public:
		CommandPool* CreateCommandPool();
		void DestroyCommandPool(CommandPool* _cmdPool);
		void DestroyAllCommandPools();

//}


//{ Buffer

	private:
		std::forward_list<Buffer*> mBuffers;

	protected:
		virtual Buffer* InstantiateBufferClass() = 0;
		virtual void DeleteBufferClass(Buffer* _pipeline);

	public:
		Buffer* CreateBuffer(uint32_t _size, BufferUsage _usage);
		void DestroyBuffer(Buffer* _pipeline);
		void DestroyAllBuffers();

//}
	};
}

#endif // SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
