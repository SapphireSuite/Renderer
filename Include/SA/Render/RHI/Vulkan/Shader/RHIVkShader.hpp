// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD

#include <SA/Render/RHI/Common/Shader/RHIShader.hpp>

#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>

namespace SA::RND::RHI
{
	class VkShader : public Shader
	{
		VK::Shader mHandle;
		
	public:
		void Create(const Device* _device, const ShaderCompileResult& _compil) override final;
		void Destroy(const Device* _device) override final;

		const VK::Shader& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_SHADER_GUARD
