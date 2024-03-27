// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_SHADER_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_SHADER_GUARD

#include <SA/Render/RHI/Common/Shader/RHIShader.hpp>

#include <SA/Render/LowLevel/DX12/Shader/D12Shader.hpp>

namespace SA::RND::RHI
{
	class D12Shader : public Shader
	{
		DX12::Shader mHandle;

	public:
		void Create(const Device* _device, const ShaderCompileResult& _compil) override final;
		void Destroy(const Device* _device) override final;

		const DX12::Shader& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_SHADER_GUARD
