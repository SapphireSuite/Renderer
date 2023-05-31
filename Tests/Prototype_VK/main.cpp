// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <dxc/dxcapi.h>
#include <dxc/WinAdapter.h>

#include <fstream>

int main()
{
	std::vector<LPWSTR> arguments;


	// // Vertex Shader
	// {
	// 	// Read file.
	// 	std::ifstream fStream("Resources/Shaders/Forward/unlit.hlsl");

	// 	if (!fStream.is_open())
	// 	{
	// 		SA_LOG(L"Failed to open file !", Error);
	// 		return -1;
	// 	}

	// 	std::string code;

	// 	std::stringstream sstream;
	// 	sstream << fStream.rdbuf();

	// 	code = sstream.str();
	// 	//


	// 	IDxcUtils* pUtils = nullptr;
	// 	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
	// 	IDxcBlobEncoding* pSource = nullptr;
	// 	pUtils->CreateBlob(code.c_str(), static_cast<uint32>(code.size()), CP_UTF8, &pSource));

	// 	arguments.push_back(L"-E");
	// 	arguments.push_back(L"mainVS");

	// 	arguments.push_back(L"-T");
	// 	arguments.push_back(L"vs_6_0");

	// 	arguments.push_back(DXC_ARG_WARNINGS_ARE_ERRORS); //-WX
	// 	arguments.push_back(DXC_ARG_DEBUG); //-Zi
	// 	arguments.push_back(DXC_ARG_PACK_MATRIX_ROW_MAJOR); //-Zp

	// 	arguments.push_back(L"-D");
	// 	arguments.push_back(L"SA_HAS_UV");

	// 	DxcBuffer sourceBuffer;
	// 	sourceBuffer.Ptr = pSource->GetBufferPointer();
	// 	sourceBuffer.Size = pSource->GetBufferSize();
	// 	sourceBuffer.Encoding = 0;

	// 	IDxcResult* pCompileResult = nullptr;

	// 	pCompiler->Compile(&sourceBuffer, arguments.data(), (uint32_t)arguments.size(), nullptr, IID_PPV_ARGS(&pCompileResult))
	// }


	CComPtr<IDxcUtils> utils = nullptr;
	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&utils));

	CComPtr<IDxcCompiler3> pCompiler;
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&pCompiler));

	// Vertex
	{
		CComPtr<IDxcBlobEncoding> sourceBlob;
		if(FAILED(utils->LoadFile(L"Resources/Shaders/Forward/unlit.hlsl", nullptr, &sourceBlob)))
		{
			SA_LOG(L"Failed to open file !", Error);
			return -1;
		}

		DxcBuffer sourceBuffer
		{
			.Ptr = sourceBlob->GetBufferPointer(),
			.Size = sourceBlob->GetBufferSize(),
			.Encoding = 0u,
		};

		std::vector<LPCWSTR> cArgs
		{
			L"-E",
			L"mainVS",
			L"-T",
			L"vs_6_5",
			L"-HV",
			L"2021",
			L"-D",
			L"SA_HAS_UV",
			DXC_ARG_WARNINGS_ARE_ERRORS,
			DXC_ARG_PACK_MATRIX_ROW_MAJOR,
			DXC_ARG_ALL_RESOURCES_BOUND,
			DXC_ARG_DEBUG
		};

		CComPtr<IDxcResult> cShader;
		
		auto result = pCompiler->Compile(&sourceBuffer,
			cArgs.data(),
			static_cast<uint32_t>(cArgs.size()),
			nullptr,
			IID_PPV_ARGS(&cShader)
		);
		
		if(FAILED(result))
			SA_LOG(L"Compilation failed!", Error);

		CComPtr<IDxcBlobUtf8> errors;
		/*SA_DX_API()*/cShader->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr);

		if (errors && errors->GetStringLength() > 0)
		{
			const std::string errorsStr = errors->GetStringPointer();
			SA_LOG(errorsStr, Error);
		}


		// Reflection
		CComPtr<IDxcBlob> reflectionBlob;
		/*SA_DX_API()*/cShader->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionBlob), nullptr);

		const DxcBuffer reflectionBuffer
		{
			.Ptr = reflectionBlob->GetBufferPointer(),
			.Size = reflectionBlob->GetBufferSize(),
			.Encoding = 0,
		};

		// CComPtr<ID3D12ShaderReflection> shaderReflection;
		// utils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&shaderReflection));
		// D3D12_SHADER_DESC shaderDesc{};
		// shaderReflection->GetDesc(&shaderDesc);
	}

	return 0;
}
