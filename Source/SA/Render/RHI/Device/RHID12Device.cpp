// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHID12Device.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	const DX12::Device* D12Device::API_DirectX12() const
	{
		return &mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
