// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIDevice.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	void Device::Destroy()
	{
		DestroyAllContexts();
	}


//{ Context

	void Device::DeleteContextClass(Context* _context)
	{
		SA_ASSERT((Nullptr, _context), SA.Render.RHI);

		delete _context;
	}

	
	Context* Device::CreateContext()
	{
		Context* const context = mContexts.emplace_front(InstantiateContextClass());

		SA_ASSERT((Nullptr, context), SA.Render.RHI, (L"Context instantiate class failed!"));

		context->Create(this);

		return context;
	}
	
	void Device::DestroyContext(Context* _context)
	{
		SA_ASSERT((Nullptr, _context), SA.Render.RHI);

		if(std::erase(mContexts, _context))
		{
			_context->Destroy();
			DeleteContextClass(_context);
		}
		else
			SA_LOG((L"Try destroy Context [%1] that does not belong to this context!", _context), Error, SA.Render.RHI);
	}

	void Device::DestroyAllContexts()
	{
		for(auto context : mContexts)
		{
			context->Destroy();
			DeleteContextClass(context);
		}

		mContexts.clear();
	}

//}


#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Device& Device::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Device& Device::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
