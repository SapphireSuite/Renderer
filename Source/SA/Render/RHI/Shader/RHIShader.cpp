// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/RHIShader.hpp>

#include <SA/Render/ShaderCompiler/ShaderCompileResult.hpp>

namespace SA::RND::RHI
{
	void Shader::Create(const Device& _device, const ShaderCompileResult& _compil)
	{
		(void)_device;
		mDescriptor = _compil.desc;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Shader& Shader::API_Vulkan() const
	{
		SA_THROW((QueryBadAPIObject, Vulkan), SA.Render.RHI.Vulkan);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Shader& Shader::API_DirectX12() const
	{
		SA_THROW((QueryBadAPIObject, DX12), SA.Render.RHI.DX12);
	}

#endif
}
