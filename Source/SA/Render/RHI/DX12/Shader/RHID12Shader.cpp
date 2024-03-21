// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/RHID12Shader.hpp>

#include <SA/Render/ShaderCompiler/ShaderCompileResult.hpp>

namespace SA::RND::RHI
{
	void D12Shader::Create(const Device* _device, const ShaderCompileResult& _compil)
	{
		Shader::Create(_device, _compil);

		mHandle.Create(_compil.dxShader);
	}
	
	void D12Shader::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}

	
	const DX12::Shader& D12Shader::API_DirectX12() const
	{
		return mHandle;
	}
}
