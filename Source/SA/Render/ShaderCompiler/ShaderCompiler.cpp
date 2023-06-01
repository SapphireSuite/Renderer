// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <ShaderCompiler.hpp>

#include <SA/Collections/Debug>

#include <ShaderIncluder.hpp>

namespace SA::RND
{
	void ShaderCompiler::Create()
	{
		SA_DXC_API(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&mUtils)));
		SA_DXC_API(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&mCompiler)));

		SA_LOG(L"Shader compiler created.", Info, SA.Render.ShaderCompiler);
	}

	void ShaderCompiler::Destroy()
	{
		mCompiler = nullptr;
		mUtils = nullptr;

		SA_LOG(L"Shader compiler destroyed.", Info, SA.Render.ShaderCompiler);
	}

	bool ShaderCompiler::ReadSourceShader(const std::wstring& _path, SourceBuffer& _src)
	{
		if(FAILED(mUtils->LoadFile(_path.c_str(), nullptr, &_src.blob)))
		{
			SA_LOG((L"Failed to open file {%1}!", _path.c_str()), Error, SA.Render.ShaderCompiler);
			return false;
		}

		_src.dx.Ptr = _src.blob->GetBufferPointer();
		_src.dx.Size = _src.blob->GetBufferSize();
		_src.dx.Encoding = 0u;

		return true;
	}

	std::vector<LPCWSTR> ShaderCompiler::ProcessParams(const ShaderCompilInfo& _info)
	{
		std::vector<LPCWSTR> cArgs
		{
			L"-E",
			_info.entrypoint.c_str(),
			L"-T",
			_info.target.c_str(),
			L"-HV",
			_info.standard.c_str(),
			DXC_ARG_WARNINGS_ARE_ERRORS,
			DXC_ARG_PACK_MATRIX_ROW_MAJOR,
			DXC_ARG_ALL_RESOURCES_BOUND,
			L"-I",
			SA_CMAKE_SOURCE_DIR L"/Resources/Shaders"
		};


	#if SA_DEBUG

		cArgs.push_back(DXC_ARG_DEBUG);

	#else

		cArgs.push_back(DXC_ARG_OPTIMIZATION_LEVEL3);

	#endif


		cArgs.reserve(_info.defines.size() * 2);
		static const wchar_t* definePreStr = L"-D";

		for(auto& define : _info.defines)
		{
			cArgs.push_back(definePreStr);
			cArgs.push_back(define.c_str());
		}

		return cArgs;
	}

	CComPtr<IDxcResult> ShaderCompiler::Compile_Internal(const DxcBuffer& _src,
		const std::vector<LPCWSTR>& _cArgs,
		const ShaderCompilInfo& _info)
	{
		ShaderIncluder includer(mUtils);
		CComPtr<IDxcResult> compilResult;
		
		SA_DXC_API(mCompiler->Compile(&_src,
			const_cast<LPCWSTR*>(_cArgs.data()),
			static_cast<uint32_t>(_cArgs.size()),
			&includer,
			IID_PPV_ARGS(&compilResult)));

		CComPtr<IDxcBlobUtf8> errors;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr));

		if (errors && errors->GetStringLength() > 0)
		{
			SA_LOG((L"Shader {%1:%2} Compilation failed!", _info.path, _info.entrypoint), Error, SA.Render.ShaderCompiler, errors->GetStringPointer());
			return nullptr;
		}

		return compilResult;
	}

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	bool ShaderCompiler::CompileDX(const ShaderCompilInfo& _info)
	{
		SourceBuffer src;
		if (!ReadSourceShader(_info.path, src))
			return false;


		std::vector<LPCWSTR> cArgs = ProcessParams(_info);
		cArgs.push_back(L"-Qstrip_reflect"); // Enable shader reflection.


		CComPtr<IDxcResult> compilResult = Compile_Internal(src.dx, cArgs, _info);

		if(!compilResult)
			return false;


	//{ Object

		CComPtr<IDxcBlob> shader;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shader), nullptr));

	//}


	//{ Reflection
	
		CComPtr<IDxcBlob> reflectionBlob;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionBlob), nullptr));

		const DxcBuffer reflectionBuffer
		{
			.Ptr = reflectionBlob->GetBufferPointer(),
			.Size = reflectionBlob->GetBufferSize(),
			.Encoding = 0,
		};

		CComPtr<ID3D12ShaderReflection> shaderReflection;
		mUtils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&shaderReflection));
		D3D12_SHADER_DESC shaderDesc{};
		shaderReflection->GetDesc(&shaderDesc);

	//}

		SA_LOG((L"Shader {%1:%2} compilation success!", _info.path, _info.entrypoint), Normal, SA.Render.ShaderCompiler);

		return true;
	}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL


#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	bool ShaderCompiler::CompileSPIRV(const ShaderCompilInfo& _info)
	{
		SourceBuffer src;
		if (!ReadSourceShader(_info.path, src))
			return false;


		std::vector<LPCWSTR> cArgs = ProcessParams(_info);
		cArgs.push_back(L"-spirv"); // Add SPIRV compile option.
		cArgs.push_back(L"-fspv-reflect"); // Aid SPIRV reflection.


		CComPtr<IDxcResult> compilResult = Compile_Internal(src.dx, cArgs, _info);

		if(!compilResult)
			return false;


	//{ Object

		CComPtr<IDxcBlob> shader;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shader), nullptr));

	//}


	//{ Reflection
	


	//}

		SA_LOG((L"Shader {%1:%2} compilation success!", _info.path, _info.entrypoint), Normal, SA.Render.ShaderCompiler);

		return true;
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
}
