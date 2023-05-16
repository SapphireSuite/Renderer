// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIContext.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	Context::~Context()
	{
		Destroy();
	}


	void Context::Create(Device* _device)
	{
		SA_ASSERT((Nullptr, _device), SA.Render.RHI, L"Instantiate Context with nullptr device!");

		mDevice = _device;

		SA_LOG(L"RHI::Context created.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}
	
	void Context::Destroy()
	{
		// Not created or Destroy() already called.
		if(!mDevice)
			return;

		DestroyAllPasses();

		mDevice = nullptr;

		SA_LOG(L"RHI::Context destroyed.", Info, SA.Render.RHI, (L"Handle [%1]", this));
	}

	
//{ Pass

	void Context::DeletePassClass(Pass* _pass)
	{
		SA_ASSERT((Nullptr, _pass), SA.Render.RHI);

		delete _pass;
	}

	Pass* Context::CreatePass(const PassDescriptor& _desc)
	{
		Pass* const pass = mPasses.emplace_front(InstantiatePassClass());

		SA_ASSERT((Nullptr, pass), SA.Render.RHI, (L"Pass instantiate class failed!"));

		pass->Create(mDevice, _desc);

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
}
