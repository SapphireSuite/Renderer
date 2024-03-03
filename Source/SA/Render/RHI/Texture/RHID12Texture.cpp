// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHID12Texture.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void D12Texture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_DirectX12(), _init->API_DirectX12(), _raw);
	}
	
	void D12Texture::Destroy(const Device* _device)
	{
		(void)_device;
		
		mHandle.Destroy();
	}


	const DX12::Texture& D12Texture::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif
