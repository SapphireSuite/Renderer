// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_CONTEXT_GUARD

#include <forward_list>

#include <SA/Render/RHI/Pass/RHIRenderPass.hpp>
#include <SA/Render/RHI/Pass/RHIFrameBuffer.hpp>
#include <SA/Render/RHI/Surface/RHISwapchain.hpp>
#include <SA/Render/RHI/Shader/RHIShader.hpp>
#include <SA/Render/RHI/Pipeline/RHIPipelineLayout.hpp>
#include <SA/Render/RHI/Pipeline/RHIPipeline.hpp>
#include <SA/Render/RHI/Pipeline/RHIRenderViews.hpp>
#include <SA/Render/RHI/Device/Command/RHICommandPool.hpp>
#include <SA/Render/RHI/Buffer/RHIBuffer.hpp>
#include <SA/Render/RHI/RHIResourceInitializer.hpp>
#include <SA/Render/RHI/Mesh/RHIStaticMesh.hpp>
#include <SA/Render/RHI/Texture/RHITexture.hpp>

namespace SA::RND::RHI
{
	class Device;

	class Context
	{
		const Device* mDevice = nullptr;

	public:
		virtual ~Context() = default;

		const Device* GetDevice() const noexcept;

		void Create(const Device* _device);
		void Destroy();


//{ RenderPass

	private:
		std::forward_list<RenderPass*> mRenderPasses;

	protected:
		virtual RenderPass* InstantiateRenderPassClass() = 0;
		virtual void DeleteRenderPassClass(RenderPass* _pass);

	public:
		RenderPass* CreateRenderPass(RenderPassInfo _info);
		void DestroyRenderPass(RenderPass* _pass);
		void DestroyAllRenderPasses();

//}


//{ FrameBuffer

	private:
		std::forward_list<FrameBuffer*> mFrameBuffers;

	protected:
		virtual FrameBuffer* InstantiateFrameBufferClass() = 0;
		virtual void DeleteFrameBufferClass(FrameBuffer* _frameBuffer);

	public:
		FrameBuffer* CreateFrameBuffer(const RenderPass* _pass, std::shared_ptr<Swapchain::BackBufferHandle> _img = nullptr);
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
		PipelineLayout* CreatePipelineLayout(const PipelineLayoutDescriptor& _desc);
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
		virtual void DeleteBufferClass(Buffer* _init);

	public:
		Buffer* CreateBuffer(uint64_t _size, BufferUsage _usage, const void* _src = nullptr);
		void DestroyBuffer(Buffer* _buffer);
		void DestroyAllBuffers();

//}


//{ ResourceInitializer

	private:
		std::forward_list<ResourceInitializer*> mResourceInitializers;

	protected:
		virtual ResourceInitializer* InstantiateResourceInitializerClass() = 0;
		virtual void DeleteResourceInitializerClass(ResourceInitializer* _init);

	public:
		ResourceInitializer* CreateResourceInitializer();
		void DestroyResourceInitializer(ResourceInitializer* _init);
		void DestroyAllResourceInitializers();

//}


//{ StaticMesh

	private:
		std::forward_list<StaticMesh*> mStaticMeshes;

	protected:
		virtual StaticMesh* InstantiateStaticMeshClass() = 0;
		virtual void DeleteStaticMeshClass(StaticMesh* _mesh);

	public:
		StaticMesh* CreateStaticMesh(ResourceInitializer* _init, const RawStaticMesh& _raw);
		void DestroyStaticMesh(StaticMesh* _mesh);
		void DestroyAllStaticMeshes();

//}


//{ Texture

	private:
		std::forward_list<Texture*> mTextures;

	protected:
		virtual Texture* InstantiateTextureClass() = 0;
		virtual void DeleteTextureClass(Texture* _texture);

	public:
		Texture* CreateTexture(const TextureDescriptor& _desc);
		Texture* CreateTexture(ResourceInitializer* _init, const RawTexture& _texture);
		void DestroyTexture(Texture* _texture);
		void DestroyAllTextures();

//}
	};
}

#endif // SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
