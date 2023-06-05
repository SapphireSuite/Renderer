// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIContext.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	void Context::Create(Device* _device)
	{
		SA_ASSERT((Nullptr, _device), SA.Render.RHI, L"Instantiate Context with nullptr device!");

		mDevice = _device;

		SA_LOG(L"RHI::Context created.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}
	
	void Context::Destroy()
	{
		DestroyAllPasses();
		DestroyAllFrameBuffers();
		DestroyAllShaders();

		mDevice = nullptr;

		SA_LOG(L"RHI::Context destroyed.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}

	
//{ Pass

	void Context::DeletePassClass(Pass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		delete _pass;
	}

	Pass* Context::CreatePass(PassInfo _info)
	{
		Pass* const pass = mPasses.emplace_front(InstantiatePassClass());

		SA_ASSERT((Nullptr, pass), SA.Render.RHI, (L"Pass instantiate class failed!"));

		pass->Create(mDevice, std::move(_info));

		return pass;
	}
	
	void Context::DestroyPass(Pass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		if(std::erase(mPasses, _pass))
		{
			_pass->Destroy(mDevice);
			DeletePassClass(_pass);
		}
		else
			SA_LOG((L"Try destroy Pass [%1] that does not belong to this context!", _pass), Error, SA.Render.RHI);
	}

	void Context::DestroyAllPasses()
	{
		for(auto pass : mPasses)
		{
			pass->Destroy(mDevice);
			DeletePassClass(pass);
		}

		mPasses.clear();
	}

//}


//{ FrameBuffer

	void Context::DeleteFrameBufferClass(FrameBuffer* _frameBuffer)
	{
		SA_ASSERT((Nullptr, _frameBuffer), SA.Render.RHI);

		delete _frameBuffer;
	}

	FrameBuffer* Context::CreateFrameBuffer(const Pass* _pass, std::shared_ptr<Swapchain::BackBufferHandle> _img)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		FrameBuffer* const frameBuffer = mFrameBuffers.emplace_front(InstantiateFrameBufferClass());

		SA_ASSERT((Nullptr, frameBuffer), SA.Render.RHI, (L"FrameBuffer instantiate class failed!"));

		frameBuffer->Create(mDevice, _pass, _img);

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
}
