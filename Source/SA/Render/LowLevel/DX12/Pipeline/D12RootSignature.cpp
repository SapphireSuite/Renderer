// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/D12RootSignature.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void RootSignature::Create(const Device& _device, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& _desc)
	{
		MComPtr<ID3DBlob> signature;
		MComPtr<ID3DBlob> error;

		SA_DX12_API(D3D12SerializeVersionedRootSignature(&_desc, &signature, &error));
		SA_DX12_API(_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(mHandle.GetAddressOf())));
		
		SA_LOG(L"Root Signature created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}
	
	void RootSignature::Destroy()
	{
		if (mHandle)
		{
			SA_LOG_RAII(L"RootSignature destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

			mHandle.Reset();
		}
	}


	DXRootSignatureT RootSignature::operator->() const
	{
		return mHandle;
	}
}
