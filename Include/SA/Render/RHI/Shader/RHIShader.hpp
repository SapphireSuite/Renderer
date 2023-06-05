// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SHADER_GUARD
#define SAPPHIRE_RENDER_RHI_SHADER_GUARD

#include "Descriptor/ShaderDescriptor.hpp"

namespace SA::RND
{
	struct ShaderCompileResult;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Shader;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Shader;
	}

#endif

	namespace RHI
	{
		class Device;

		class Shader
		{
		protected:
			ShaderDescriptor mDescriptor;

		public:
			virtual ~Shader() = default;

			virtual void Create(const Device* _device, const ShaderCompileResult& _compil);
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
			virtual const VK::Shader& API_Vulkan() const;
#endif

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
			virtual const DX12::Shader& API_DirectX12() const;
#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_SHADER_GUARD
