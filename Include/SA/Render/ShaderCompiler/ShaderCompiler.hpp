// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_COMPILER_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPILER_GUARD

#include "DXCAPI.hpp"

#include "ShaderCompileInfo.hpp"
#include "ShaderCompileResult.hpp"

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
		std::vector<LPCWSTR> ProcessParams(const ShaderCompileInfo& _info, std::list<std::wstring>& _strBuff);
		CComPtr<IDxcResult> Compile_Internal(const DxcBuffer& _src,
			const std::vector<LPCWSTR>& _cArgs,
			const ShaderCompileInfo& _info,
			ShaderCompileResult& _result);

	public:
		void Create();
		void Destroy();

	#if SA_RENDER_LOWLEVEL_DX12_IMPL
	private:
		bool ReflectDX(CComPtr<IDxcBlob> _reflectionBlob, RHI::ShaderDescriptor& _desc);

	public:
		ShaderCompileResult CompileDX(const ShaderCompileInfo& _info);
	#endif

	#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENGL_IMPL
	private:
		bool ReflectSPIRV(CComPtr<IDxcBlob> _shader, RHI::ShaderDescriptor& _desc);

	public:
		ShaderCompileResult CompileSPIRV(const ShaderCompileInfo& _info);
	#endif
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILER_GUARD
