// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHID12DeviceInfo.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	uint32_t D12DeviceInfo::GetScore() const
	{
		return mHandle.score;
	}


	std::wstring D12DeviceInfo::GetName() const
	{
		return mHandle.desc.Description;
	}


	uint32_t D12DeviceInfo::GetID() const
	{
		return mHandle.desc.DeviceId;
	}
	
	uint32_t D12DeviceInfo::GetVendorID() const
	{
		return mHandle.desc.VendorId;
	}


	const DX12::DeviceInfo* D12DeviceInfo::API_DirectX12() const
	{
		return &mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
