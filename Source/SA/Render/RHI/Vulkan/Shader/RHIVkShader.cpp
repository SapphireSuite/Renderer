// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/RHIVkShader.hpp>

#include <Device/RHIVkDevice.hpp>

#include <SA/Render/ShaderCompiler/ShaderCompileResult.hpp>

namespace SA::RND::RHI
{
	void VkShader::Create(const Device* _device, const ShaderCompileResult& _compil)
	{
		Shader::Create(_device, _compil);

		mHandle.Create(_device->API_Vulkan(), _compil.rawSPIRV);
	}

	void VkShader::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}


	const VK::Shader& VkShader::API_Vulkan() const
	{
		return mHandle;
	}
}
