// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHID12Pass.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void D12Pass::Create(const Device* _device, PassInfo _info)
	{
		Pass::Create(_device, std::move(_info));
	}
	
	void D12Pass::Destroy(const Device* _device)
	{
		(void)_device;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
