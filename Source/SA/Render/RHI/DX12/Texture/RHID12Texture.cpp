// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Texture/RHID12Texture.hpp>

#include <Device/RHID12Device.hpp>
#include <RHID12ResourceInitializer.hpp>

namespace SA::RND::RHI
{
	void D12Texture::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw)
	{
		mHandle.Create(_device->API_DirectX12(), _init->API_DirectX12(), _raw);
	}

	void D12Texture::Create(const Device* _device, const TextureDescriptor& _desc)
	{
		mHandle.Create(_device->API_DirectX12(), _desc.API_DirectX12());
	}

	void D12Texture::CreateFromImage(const Swapchain* _swapchain, uint32_t _imageIndex)
	{
		mHandle.CreateFromImage(_swapchain->API_DirectX12(), _imageIndex);
	}

	void D12Texture::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}


	DX12::Texture& D12Texture::API_DirectX12()
	{
		return mHandle;
	}

	const DX12::Texture& D12Texture::API_DirectX12() const
	{
		return mHandle;
	}
}
