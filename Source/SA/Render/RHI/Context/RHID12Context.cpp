// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHID12Context.hpp>

#include <Pass/RHID12Pass.hpp>
#include <Pass/RHID12FrameBuffer.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	Pass* D12Context::InstantiatePassClass()
	{
		return new D12Pass();
	}
	
	FrameBuffer* D12Context::InstantiateFrameBufferClass()
	{
		return new D12FrameBuffer();
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
