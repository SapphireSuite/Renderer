// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHID12Context.hpp>

#include <Pass/RHID12Pass.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	Pass* D12Context::InstantiatePassClass()
	{
		return new D12Pass();
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
