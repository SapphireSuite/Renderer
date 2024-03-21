// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHID12Cubemap.hpp>

#include <Device/RHID12Device.hpp>

namespace SA::RND::RHI
{
	void D12Cubemap::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawCubemap& _raw)
	{
		mHandle.Create(_device->API_DirectX12(), _init->API_DirectX12(), _raw);
	}
	
	void D12Cubemap::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}

	
	const DX12::Cubemap& D12Cubemap::API_DirectX12() const
	{
		return mHandle;
	}
}
