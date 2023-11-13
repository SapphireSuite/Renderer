// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/D12Shader.hpp>

namespace SA::RND::DX12
{
	void Shader::Create(MComPtr<ID3DBlob> _handle)
	{
		mHandle = _handle;

		SA_LOG(L"Shader created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}
	
	void Shader::Destroy()
	{
		SA_LOG_RAII(L"Shader destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
		
		mHandle.Reset();
	}

	ID3DBlob* Shader::operator->() const noexcept
	{
		return mHandle.Get();
	}
}
