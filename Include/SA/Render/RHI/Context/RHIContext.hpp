// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_CONTEXT_GUARD

#include <forward_list>

#include <SA/Render/RHI/Pass/RHIPass.hpp>

namespace SA::RND::RHI
{
	class Device;

	class Context
	{
		Device* mDevice = nullptr;

	public:
		virtual ~Context() = 0;

		void Create(Device* _device);
		void Destroy();

//{ Pass

	private:
		std::forward_list<Pass*> mPasses;

	protected:
		virtual Pass* InstantiatePassClass() = 0;
		virtual void DeletePassClass(Pass* _pass);

	public:
		Pass* CreatePass(const PassInfo& _info);
		void DestroyPass(Pass* _pass);
		void DestroyAllPasses();

//}

	};
}

#endif // SAPPHIRE_RENDER_RHI_CONTEXT_GUARD
