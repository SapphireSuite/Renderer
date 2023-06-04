// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD

#include <string>
#include <unordered_set>

#include <SA/Render/LowLevel/Common/Shader/RawShader.hpp>
#include <SA/Render/RHI/Shader/Descriptor/ShaderDescriptor.hpp>

namespace SA::RND
{
	struct ShaderCompileResult
	{
		bool bSuccess = false;

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		/// Shader Data used for DX12.
		CComPtr<IDxcBlob> dxShader;

#endif

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENLG_IMPL
		/// Raw shader from SPIRV compilation used for OpenGL/Vulkans
		RawShader rawSPIRV;
#endif

		std::unordered_set<std::wstring> includedFiles;

		RHI::ShaderDescriptor desc;

		inline operator bool() const noexcept { return bSuccess; }
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD
