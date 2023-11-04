// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHID12ResourceInitializer.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void D12ResourceInitializer::Create(const Device* _device)
	{
		mHandle.Create(_device->API_DirectX12());
	}

	void D12ResourceInitializer::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}


	DX12::ResourceInitializer& D12ResourceInitializer::API_DirectX12()
	{
		return mHandle;
	}
}

#endif
