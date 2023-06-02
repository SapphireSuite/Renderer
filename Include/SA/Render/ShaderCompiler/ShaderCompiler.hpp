// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_COMPILER_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPILER_GUARD

#include "DXCAPI.hpp"

#include "ShaderCompilInfo.hpp"

namespace SA::RND
{
	class ShaderCompiler
	{
		CComPtr<IDxcUtils> mUtils;
		CComPtr<IDxcCompiler3> mCompiler;

		struct SourceBuffer
		{
			CComPtr<IDxcBlobEncoding> blob;
			DxcBuffer dx;
		};

		bool ReadSourceShader(const std::wstring& _path, SourceBuffer& _src);
		std::vector<LPCWSTR> ProcessParams(const ShaderCompilInfo& _info);
		CComPtr<IDxcResult> Compile_Internal(const DxcBuffer& _src,
			const std::vector<LPCWSTR>& _cArgs,
			const ShaderCompilInfo& _info);

	#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENLG_IMPL
		void ReflectSPIRV(CComPtr<IDxcBlob> _shader);
	#endif

	public:
		void Create();
		void Destroy();

	#if SA_RENDER_LOWLEVEL_DX12_IMPL
		bool CompileDX(const ShaderCompilInfo& _info);
	#endif

	#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENLG_IMPL
		bool CompileSPIRV(const ShaderCompilInfo& _info);
	#endif
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILER_GUARD
