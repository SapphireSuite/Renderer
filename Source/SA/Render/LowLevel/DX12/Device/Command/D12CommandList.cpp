// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/D12CommandList.hpp>

namespace SA::RND::DX12
{
	ID3D12GraphicsCommandList* CommandList::Get() const
	{
		return mHandle.Get();
	}
	
	ID3D12GraphicsCommandList* CommandList::operator->() const
	{
		return mHandle.Get();
	}
}
