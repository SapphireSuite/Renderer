// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIContext.hpp>

#include <SA/Collections/Debug>

#include <SA/Render/ShaderCompiler/ShaderCompileResult.hpp>

namespace SA::RND::RHI
{
	const Device* Context::GetDevice() const noexcept
	{
		return mDevice;
	}

	void Context::Create(const Device* _device)
	{
		SA_ASSERT((Nullptr, _device), SA.Render.RHI, L"Instantiate Context with nullptr device!");

		mDevice = _device;

		SA_LOG(L"RHI::Context created.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}
	
	void Context::Destroy()
	{
		DestroyAllStaticMeshes();
		DestroyAllResourceInitializers();
		DestroyAllBuffers();
		DestroyAllCommandPools();
		DestroyAllPipelines();
		DestroyAllPipelineLayouts();
		DestroyAllShaders();
		DestroyAllFrameBuffers();
		DestroyAllRenderPasses();

		mDevice = nullptr;

		SA_LOG(L"RHI::Context destroyed.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}

	
//{ RenderPass

	void Context::DeleteRenderPassClass(RenderPass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		delete _pass;
	}

	RenderPass* Context::CreateRenderPass(RenderPassInfo _info)
	{
		RenderPass* const pass = mRenderPasses.emplace_front(InstantiateRenderPassClass());

		SA_ASSERT((Nullptr, pass), SA.Render.RHI, (L"RenderPass instantiate class failed!"));

		pass->Create(mDevice, std::move(_info));

		return pass;
	}
	
	void Context::DestroyRenderPass(RenderPass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		if(std::erase(mRenderPasses, _pass))
		{
			_pass->Destroy(mDevice);
			DeleteRenderPassClass(_pass);
		}
		else
			SA_LOG((L"Try destroy RenderPass [%1] that does not belong to this context!", _pass), Error, SA.Render.RHI);
	}

	void Context::DestroyAllRenderPasses()
	{
		for(auto pass : mRenderPasses)
		{
			pass->Destroy(mDevice);
			DeleteRenderPassClass(pass);
		}

		mRenderPasses.clear();
	}

//}


//{ FrameBuffer

	void Context::DeleteFrameBufferClass(FrameBuffer* _frameBuffer)
	{
		SA_ASSERT((Nullptr, _frameBuffer), SA.Render.RHI);

		delete _frameBuffer;
	}

	FrameBuffer* Context::CreateFrameBuffer(const RenderPass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		FrameBuffer* const frameBuffer = mFrameBuffers.emplace_front(InstantiateFrameBufferClass());

		SA_ASSERT((Nullptr, frameBuffer), SA.Render.RHI, (L"FrameBuffer instantiate class failed!"));

		frameBuffer->Create(mDevice, _pass);

		return frameBuffer;
	}
	
	void Context::DestroyFrameBuffer(FrameBuffer* _frameBuffer)
	{
		SA_ASSERT((Nullptr, _frameBuffer), SA.Render.RHI);

		if(std::erase(mFrameBuffers, _frameBuffer))
		{
			_frameBuffer->Destroy(mDevice);
			DeleteFrameBufferClass(_frameBuffer);
		}
		else
			SA_LOG((L"Try destroy FrameBuffer [%1] that does not belong to this context!", _frameBuffer), Error, SA.Render.RHI);
	}

	void Context::DestroyAllFrameBuffers()
	{
		for(auto frameBuffer : mFrameBuffers)
		{
			frameBuffer->Destroy(mDevice);
			DeleteFrameBufferClass(frameBuffer);
		}

		mFrameBuffers.clear();
	}

//}


//{ Shader

	void Context::DeleteShaderClass(Shader* _shader)
	{
		SA_ASSERT((Nullptr, _shader), SA.Render.RHI);

		delete _shader;
	}

	Shader* Context::CreateShader(const ShaderCompileResult& _comp)
	{
		SA_ASSERT((Default, _comp.bSuccess), SA.Render.RHI, L"Try creating shader from failed compilation result!");

		Shader* const shader = mShaders.emplace_front(InstantiateShaderClass());

		SA_ASSERT((Nullptr, shader), SA.Render.RHI, (L"Shader instantiate class failed!"));

		shader->Create(mDevice, _comp);

		return shader;
	}

	void Context::DestroyShader(Shader* _shader)
	{
		SA_ASSERT((Nullptr, _shader), SA.Render.RHI);

		if (std::erase(mShaders, _shader))
		{
			_shader->Destroy(mDevice);
			DeleteShaderClass(_shader);
		}
		else
			SA_LOG((L"Try destroy Shader [%1] that does not belong to this context!", _shader), Error, SA.Render.RHI);
	}

	void Context::DestroyAllShaders()
	{
		for (auto shader : mShaders)
		{
			shader->Destroy(mDevice);
			DeleteShaderClass(shader);
		}

		mShaders.clear();
	}

//}


//{ RenderViews

	void Context::DeleteRenderViewsClass(RenderViews* _views)
	{
		SA_ASSERT((Nullptr, _views), SA.Render.RHI);

		delete _views;
	}

	RenderViews* Context::CreateRenderViews()
	{
		RenderViews* const views = mRenderViews.emplace_front(InstantiateRenderViewsClass());

		SA_ASSERT((Nullptr, views), SA.Render.RHI, (L"RenderViews instantiate class failed!"));

		return views;
	}

	void Context::DestroyRenderViews(RenderViews* _views)
	{
		SA_ASSERT((Nullptr, _views), SA.Render.RHI);

		if (std::erase(mRenderViews, _views))
		{
			DeleteRenderViewsClass(_views);
		}
		else
			SA_LOG((L"Try destroy RenderViews [%1] that does not belong to this context!", _views), Error, SA.Render.RHI);
	}

	void Context::DestroyAllRenderViews()
	{
		for (auto views : mRenderViews)
		{
			DeleteRenderViewsClass(views);
		}

		mRenderViews.clear();
	}

//}


//{ PipelineLayout

	void Context::DeletePipelineLayoutClass(PipelineLayout* _pipLayout)
	{
		SA_ASSERT((Nullptr, _pipLayout), SA.Render.RHI);

		delete _pipLayout;
	}

	PipelineLayout* Context::CreatePipelineLayout(const PipelineLayoutDescriptor& _desc)
	{
		PipelineLayout* const pipLayout = mPipelineLayouts.emplace_front(InstantiatePipelineLayoutClass());

		SA_ASSERT((Nullptr, pipLayout), SA.Render.RHI, (L"PipelineLayout instantiate class failed!"));

		pipLayout->Create(mDevice, _desc);

		return pipLayout;
	}

	void Context::DestroyPipelineLayout(PipelineLayout* _pipLayout)
	{
		SA_ASSERT((Nullptr, _pipLayout), SA.Render.RHI);

		if (std::erase(mPipelineLayouts, _pipLayout))
		{
			_pipLayout->Destroy(mDevice);
			DeletePipelineLayoutClass(_pipLayout);
		}
		else
			SA_LOG((L"Try destroy PipelineLayout [%1] that does not belong to this context!", _pipLayout), Error, SA.Render.RHI);
	}

	void Context::DestroyAllPipelineLayouts()
	{
		for (auto pipLayout : mPipelineLayouts)
		{
			pipLayout->Destroy(mDevice);
			DeletePipelineLayoutClass(pipLayout);
		}

		mPipelineLayouts.clear();
	}

//}


//{ Pipeline

	void Context::DeletePipelineClass(Pipeline* _pipeline)
	{
		SA_ASSERT((Nullptr, _pipeline), SA.Render.RHI);

		delete _pipeline;
	}

	Pipeline* Context::CreatePipeline(const GraphicsPipelineInfo& _info)
	{
		SA_ASSERT((Nullptr, _info.pass), SA.Render>RHI, L"Graphics Pipeline creation requires a valid Pass.");
		SA_ASSERT((Nullptr, _info.layout), SA.Render>RHI, L"Graphics Pipeline creation requires a valid PipelineLayout.");

		Pipeline* const pipeline = mPipelines.emplace_front(InstantiatePipelineClass());

		SA_ASSERT((Nullptr, pipeline), SA.Render.RHI, (L"Pipeline instantiate class failed!"));

		pipeline->Create(mDevice, _info);

		return pipeline;
	}

	void Context::DestroyPipeline(Pipeline* _pipeline)
	{
		SA_ASSERT((Nullptr, _pipeline), SA.Render.RHI);

		if (std::erase(mPipelines, _pipeline))
		{
			_pipeline->Destroy(mDevice);
			DeletePipelineClass(_pipeline);
		}
		else
			SA_LOG((L"Try destroy Pipeline [%1] that does not belong to this context!", _pipeline), Error, SA.Render.RHI);
	}

	void Context::DestroyAllPipelines()
	{
		for (auto pipeline : mPipelines)
		{
			pipeline->Destroy(mDevice);
			DeletePipelineClass(pipeline);
		}

		mPipelines.clear();
	}

//}


//{ CommandPool

	void Context::DeleteCommandPoolClass(CommandPool* _cmdPool)
	{
		SA_ASSERT((Nullptr, _cmdPool), SA.Render.RHI);

		delete _cmdPool;
	}

	CommandPool* Context::CreateCommandPool()
	{
		CommandPool* const cmdPool = mCommandPools.emplace_front(InstantiateCommandPoolClass());

		SA_ASSERT((Nullptr, cmdPool), SA.Render.RHI, (L"CommandPool instantiate class failed!"));

		cmdPool->Create(mDevice);

		return cmdPool;
	}

	void Context::DestroyCommandPool(CommandPool* _cmdPool)
	{
		SA_ASSERT((Nullptr, _cmdPool), SA.Render.RHI);

		if (std::erase(mCommandPools, _cmdPool))
		{
			_cmdPool->Destroy(mDevice);
			DeleteCommandPoolClass(_cmdPool);
		}
		else
			SA_LOG((L"Try destroy CommandPool [%1] that does not belong to this context!", _cmdPool), Error, SA.Render.RHI);
	}

	void Context::DestroyAllCommandPools()
	{
		for (auto cmdPool : mCommandPools)
		{
			cmdPool->Destroy(mDevice);
			DeleteCommandPoolClass(cmdPool);
		}

		mCommandPools.clear();
	}

//}


//{ Buffer

	void Context::DeleteBufferClass(Buffer* _buffer)
	{
		SA_ASSERT((Nullptr, _buffer), SA.Render.RHI);

		delete _buffer;
	}

	Buffer* Context::CreateBuffer(uint64_t _size, BufferUsage _usage, const void* _src)
	{
		Buffer* const buffer = mBuffers.emplace_front(InstantiateBufferClass());

		SA_ASSERT((Nullptr, buffer), SA.Render.RHI, (L"Buffer instantiate class failed!"));

		buffer->Create(mDevice, _size, _usage, _src);

		return buffer;
	}

	void Context::DestroyBuffer(Buffer* _buffer)
	{
		SA_ASSERT((Nullptr, _buffer), SA.Render.RHI);

		if (std::erase(mBuffers, _buffer))
		{
			_buffer->Destroy(mDevice);
			DeleteBufferClass(_buffer);
		}
		else
			SA_LOG((L"Try destroy Buffer [%1] that does not belong to this context!", _buffer), Error, SA.Render.RHI);
	}

	void Context::DestroyAllBuffers()
	{
		for (auto buffer : mBuffers)
		{
			buffer->Destroy(mDevice);
			DeleteBufferClass(buffer);
		}

		mBuffers.clear();
	}

//}


//{ ResourceInitializer

	void Context::DeleteResourceInitializerClass(ResourceInitializer* _init)
	{
		SA_ASSERT((Nullptr, _init), SA.Render.RHI);

		delete _init;
	}

	ResourceInitializer* Context::CreateResourceInitializer()
	{
		ResourceInitializer* const init = mResourceInitializers.emplace_front(InstantiateResourceInitializerClass());

		SA_ASSERT((Nullptr, init), SA.Render.RHI, (L"ResourceInitializer instantiate class failed!"));

		init->Create(mDevice);

		return init;
	}

	void Context::DestroyResourceInitializer(ResourceInitializer* _init)
	{
		SA_ASSERT((Nullptr, _init), SA.Render.RHI);

		if (std::erase(mResourceInitializers, _init))
		{
			_init->Destroy();
			DeleteResourceInitializerClass(_init);
		}
		else
			SA_LOG((L"Try destroy ResourceInitializer [%1] that does not belong to this context!", _init), Error, SA.Render.RHI);
	}

	void Context::DestroyAllResourceInitializers()
	{
		for (auto init : mResourceInitializers)
		{
			init->Destroy();
			DeleteResourceInitializerClass(init);
		}

		mResourceInitializers.clear();
	}

//}


//{ StaticMesh

	void Context::DeleteStaticMeshClass(StaticMesh* _mesh)
	{
		SA_ASSERT((Nullptr, _mesh), SA.Render.RHI);

		delete _mesh;
	}

	StaticMesh* Context::CreateStaticMesh(ResourceInitializer* _init, const RawStaticMesh& _raw)
	{
		StaticMesh* const mesh = mStaticMeshes.emplace_front(InstantiateStaticMeshClass());

		SA_ASSERT((Nullptr, mesh), SA.Render.RHI, (L"StaticMesh instantiate class failed!"));

		mesh->Create(mDevice, _init, _raw);

		return mesh;
	}

	void Context::DestroyStaticMesh(StaticMesh* _mesh)
	{
		SA_ASSERT((Nullptr, _mesh), SA.Render.RHI);

		if (std::erase(mStaticMeshes, _mesh))
		{
			_mesh->Destroy(mDevice);
			DeleteStaticMeshClass(_mesh);
		}
		else
			SA_LOG((L"Try destroy StaticMesh [%1] that does not belong to this context!", _mesh), Error, SA.Render.RHI);
	}

	void Context::DestroyAllStaticMeshes()
	{
		for (auto mesh : mStaticMeshes)
		{
			mesh->Destroy(mDevice);
			DeleteStaticMeshClass(mesh);
		}

		mStaticMeshes.clear();
	}

//}


//{ Textures

	void Context::DeleteTextureClass(Texture* _texture)
	{
		SA_ASSERT((Nullptr, _texture), SA.Render.RHI);

		delete _texture;
	}


	Texture* Context::CreateTexture(const Swapchain* _swapchain, uint32_t _imageIndex)
	{
		Texture* const texture = mTextures.emplace_front(InstantiateTextureClass());

		SA_ASSERT((Nullptr, texture), SA.Render.RHI, (L"Texture instantiate class failed!"));

		texture->CreateFromImage(_swapchain, _imageIndex);

		return texture;
	}

	Texture* Context::CreateTexture(const TextureDescriptor& _desc)
	{
		Texture* const texture = mTextures.emplace_front(InstantiateTextureClass());

		SA_ASSERT((Nullptr, texture), SA.Render.RHI, (L"Texture instantiate class failed!"));

		texture->Create(mDevice, _desc);

		return texture;
	}

	Texture* Context::CreateTexture(ResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = mTextures.emplace_front(InstantiateTextureClass());

		SA_ASSERT((Nullptr, texture), SA.Render.RHI, (L"Texture instantiate class failed!"));

		texture->Create(mDevice, _init, _raw);

		return texture;
	}

	void Context::DestroyTexture(Texture* _texture)
	{
		SA_ASSERT((Nullptr, _texture), SA.Render.RHI);

		if (std::erase(mTextures, _texture))
		{
			_texture->Destroy(mDevice);
			DeleteTextureClass(_texture);
		}
		else
			SA_LOG((L"Try destroy Texture [%1] that does not belong to this context!", _texture), Error, SA.Render.RHI);
	}

	void Context::DestroyAllTextures()
	{
		for (auto texture: mTextures)
		{
			texture->Destroy(mDevice);
			DeleteTextureClass(texture);
		}

		mTextures.clear();
	}

//}
}
