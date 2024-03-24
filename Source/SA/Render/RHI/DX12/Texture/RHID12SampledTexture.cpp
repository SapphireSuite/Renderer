// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHID12SampledTexture.hpp>

#include <Device/RHID12Device.hpp>
#include <RHID12ResourceInitializer.hpp>

namespace SA::RND::RHI
{
	void D12SampledTexture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_DirectX12(), _init->API_DirectX12(), _raw);
	}

	void D12SampledTexture::Destroy(const Device* _device)
	{
		mHandle.Destroy();
	}
}
