// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <ShaderCompiler.hpp>

#include <SA/Collections/Debug>

#include "ShaderIncluder.hpp"
#include "SPIRV-ReflectAPI.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL
#include <d3d12shader.h>
#endif

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

	std::vector<LPCWSTR> ShaderCompiler::ProcessParams(const ShaderCompileInfo& _info, std::list<std::wstring>& _strBuff)
	{
		std::wstring& wEntrypoint = _strBuff.emplace_back(SA::ToWString(_info.entrypoint));
		std::wstring& wTarget = _strBuff.emplace_back(SA::ToWString(_info.target));
		std::wstring& wStandard = _strBuff.emplace_back(SA::ToWString(_info.standard));

		std::vector<LPCWSTR> cArgs
		{
			L"-E",
			wEntrypoint.c_str(),
			L"-T",
			wTarget.c_str(),
			L"-HV",
			wStandard.c_str(),
			DXC_ARG_WARNINGS_ARE_ERRORS,
			DXC_ARG_PACK_MATRIX_ROW_MAJOR,
			DXC_ARG_ALL_RESOURCES_BOUND,
			L"-I",
			SA_WIDE(SA_CMAKE_SOURCE_DIR) L"/Resources/Shaders",
			L"-I",
			L"/Resources/Shaders"
		};


	#if SA_DEBUG

		cArgs.push_back(DXC_ARG_DEBUG);

	#else

		cArgs.push_back(DXC_ARG_OPTIMIZATION_LEVEL3);

	#endif


		cArgs.reserve(defines.size() + _info.defines.size() * 2);

		// Common defines.
		for (auto& define : defines)
		{
			std::wstring& wDefine = _strBuff.emplace_back(SA::ToWString(define));

			cArgs.push_back(L"-D");
			cArgs.push_back(wDefine.c_str());
		}

		// Instance-specific defines.
		for(auto& define : _info.defines)
		{
			std::wstring& wDefine = _strBuff.emplace_back(SA::ToWString(define));

			cArgs.push_back(L"-D");
			cArgs.push_back(wDefine.c_str());
		}

		return cArgs;
	}

	CComPtr<IDxcResult> ShaderCompiler::Compile_Internal(const DxcBuffer& _src,
		const std::vector<LPCWSTR>& _cArgs,
		const ShaderCompileInfo& _info,
		ShaderCompileResult& _result)
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

		_result.includedFiles = std::move(includer.includedFiles);

		_result.desc.entrypoint = _info.entrypoint;
		_result.desc.stage = RHI::GetShaderStageFromTarget(_info.target);

		return compilResult;
	}

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	
	namespace DX12
	{
		uint32_t ComputeComponentNum(BYTE _mask)
		{
			uint32_t componentNum = 0;

			for (int i = 0; i < 4; ++i)
			{
				if (_mask & 0x1)
					++componentNum;

				_mask >>= 1;
			}

			return componentNum;
		}

		RHI::Format ComputeFormat(D3D_REGISTER_COMPONENT_TYPE _cType, uint32_t _cNum)
		{
			switch (_cType)
			{
			case D3D_REGISTER_COMPONENT_FLOAT32:
			{
				constexpr RHI::Format sFormats[]{
					RHI::Format::Unknown,
					RHI::Format::R32_SFLOAT,
					RHI::Format::R32G32_SFLOAT,
					RHI::Format::R32G32B32_SFLOAT,
					RHI::Format::R32G32B32A32_SFLOAT
				};

				return sFormats[_cNum];
			}
			case D3D_REGISTER_COMPONENT_UINT32:
			{
				constexpr RHI::Format sFormats[]{
					RHI::Format::Unknown,
					RHI::Format::R32_UINT,
					RHI::Format::R32G32_UINT,
					RHI::Format::R32G32B32_UINT,
					RHI::Format::R32G32B32A32_UINT
				};

				return sFormats[_cNum];
			}
			case D3D_REGISTER_COMPONENT_SINT32:
			{
				constexpr RHI::Format sFormats[]{
					RHI::Format::Unknown,
					RHI::Format::R32_SINT,
					RHI::Format::R32G32_SINT,
					RHI::Format::R32G32B32_SINT,
					RHI::Format::R32G32B32A32_SINT
				};

				return sFormats[_cNum];
			}
			default:
				return RHI::Format::Unknown;
			}
		}

		uint32_t ComputeComponentSize(D3D_REGISTER_COMPONENT_TYPE _cType, uint32_t _cNum)
		{
			switch (_cType)
			{
				case D3D_REGISTER_COMPONENT_FLOAT32:
					return sizeof(float) * _cNum;
				case D3D_REGISTER_COMPONENT_UINT32:
				case D3D_REGISTER_COMPONENT_SINT32:
					return sizeof(uint32_t) * _cNum;
				default:
					return 0;
			}
		}

		static const RHI::ShaderBindingType sBindingTypeMap[] = {
			RHI::ShaderBindingType::UniformConstantBuffer,
			(RHI::ShaderBindingType)0,
			RHI::ShaderBindingType::Texture,
			RHI::ShaderBindingType::Sampler,
		};
	}

	bool ShaderCompiler::ReflectDX(CComPtr<IDxcBlob> _reflectionBlob, RHI::ShaderDescriptor& _desc)
	{
		const DxcBuffer reflectionBuffer
		{
			.Ptr = _reflectionBlob->GetBufferPointer(),
			.Size = _reflectionBlob->GetBufferSize(),
			.Encoding = 0,
		};

		CComPtr<ID3D12ShaderReflection> shaderReflection;
		SA_DXC_API(mUtils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&shaderReflection)));

		D3D12_SHADER_DESC inShaderDesc{};
		shaderReflection->GetDesc(&inShaderDesc);

		// Inputs.
		for (uint32_t i = 0; i < inShaderDesc.InputParameters; ++i)
		{
			D3D12_SIGNATURE_PARAMETER_DESC inInput;
			shaderReflection->GetInputParameterDesc(i, &inInput);

			auto& outInput = _desc.inputs.emplace_back();

			outInput.semantic = inInput.SemanticName;
			outInput.reg = inInput.Register;

			const uint32_t componentNum = DX12::ComputeComponentNum(inInput.Mask);

			outInput.format = DX12::ComputeFormat(inInput.ComponentType, componentNum);
			outInput.size = DX12::ComputeComponentSize(inInput.ComponentType, componentNum);
		}


		// Bindings
		{
			for (uint32_t i = 0; i < inShaderDesc.BoundResources; ++i)
			{
				D3D12_SHADER_INPUT_BIND_DESC inDesc;
				shaderReflection->GetResourceBindingDesc(i, &inDesc);

				auto& outDescSet = _desc.GetOrEmplaceSet(inDesc.Space);
				auto& outDesc = outDescSet.bindings.emplace_back();

				outDesc.name = inDesc.Name;
				outDesc.binding = inDesc.BindPoint;
				outDesc.num = inDesc.BindCount;
				outDesc.type = DX12::sBindingTypeMap[(uint32_t)inDesc.Type];
			}
		}


		return true;
	}

	ShaderCompileResult ShaderCompiler::CompileDX(const ShaderCompileInfo& _info)
	{
		ShaderCompileResult result;

		SourceBuffer src;
		if (!ReadSourceShader(_info.path, src))
			return result;

		std::list<std::wstring> strBuff;
		std::vector<LPCWSTR> cArgs = ProcessParams(_info, strBuff);
		cArgs.push_back(L"-Qstrip_reflect"); // Enable shader reflection.


		CComPtr<IDxcResult> compilResult = Compile_Internal(src.dx, cArgs, _info, result);

		if(!compilResult)
			return result;


		SA_DXC_API(compilResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&result.dxShader), nullptr));


		CComPtr<IDxcBlob> reflectionBlob;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionBlob), nullptr));

		if (!ReflectDX(reflectionBlob, result.desc))
			return result;


		result.bSuccess = true;
		SA_LOG((L"Shader {%1:%2} compilation success!", _info.path, _info.entrypoint), Normal, SA.Render.ShaderCompiler);

		return result;
	}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL


#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENGL_IMPL

	namespace SPV
	{
		static const RHI::Format sFormatIndexMap[] = {
			RHI::Format::R32_UINT,
			RHI::Format::R32_SINT,
			RHI::Format::R32_SFLOAT,

			RHI::Format::R32G32_UINT,
			RHI::Format::R32G32_SINT,
			RHI::Format::R32G32_SFLOAT,

			RHI::Format::R32G32B32_UINT,
			RHI::Format::R32G32B32_SINT,
			RHI::Format::R32G32B32_SFLOAT,

			RHI::Format::R32G32B32A32_UINT,
			RHI::Format::R32G32B32A32_SINT,
			RHI::Format::R32G32B32A32_SFLOAT,
		};

		RHI::Format API_GetFormat(SpvReflectFormat _spvFormat)
		{
			// SpvReflectFormat enum does *not* start at 0: remove offset.
			const uint32_t index = static_cast<uint32_t>(_spvFormat - SPV_REFLECT_FORMAT_R32_UINT);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(sFormatIndexMap)), SA.Render.ShaderCompiler.SPV,
				(L"Format value [%1] invalid", index));

			return sFormatIndexMap[index];
		}


		static const uint32_t sSizeIndexMap[] = {
			sizeof(uint32_t),
			sizeof(uint32_t),
			sizeof(float),

			2 * sizeof(uint32_t),
			2 * sizeof(uint32_t),
			2 * sizeof(float),

			3 * sizeof(uint32_t),
			3 * sizeof(uint32_t),
			3 * sizeof(float),

			4 * sizeof(uint32_t),
			4 * sizeof(uint32_t),
			4 * sizeof(float),
		};

		static const RHI::ShaderBindingType sBindingTypeMap[] = {
			RHI::ShaderBindingType::Sampler,
			RHI::ShaderBindingType::Texture,
			RHI::ShaderBindingType::Texture,
			(RHI::ShaderBindingType)0,
			(RHI::ShaderBindingType)0,
			(RHI::ShaderBindingType)0,
			RHI::ShaderBindingType::UniformConstantBuffer,
			RHI::ShaderBindingType::StorageBuffer,
			(RHI::ShaderBindingType)0,
			(RHI::ShaderBindingType)0,
			RHI::ShaderBindingType::InputAttachment,
		};

		uint32_t API_GetSizeFromFormat(SpvReflectFormat _spvFormat)
		{
			// SpvReflectFormat enum does *not* start at 0: remove offset.
			const uint32_t index = static_cast<uint32_t>(_spvFormat - SPV_REFLECT_FORMAT_R32_UINT);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(sSizeIndexMap)), SA.Render.ShaderCompiler.SPV,
				(L"Format value [%1] invalid", index));

			return sSizeIndexMap[index];
		}
	}

	bool ShaderCompiler::ReflectSPIRV(CComPtr<IDxcBlob> _shader, RHI::ShaderDescriptor& _desc)
	{
		SpvReflectShaderModule module;
		SA_SPIRVR_API(spvReflectCreateShaderModule(_shader->GetBufferSize(), _shader->GetBufferPointer(), &module));

		// Inputs
		{
			uint32_t count = 0u;
			spvReflectEnumerateInputVariables(&module, &count, nullptr);
			std::vector<SpvReflectInterfaceVariable*> inputs(count);
			spvReflectEnumerateInputVariables(&module, &count, inputs.data());

			for (auto inInput : inputs)
			{
				// Skip system input type (ex: SV_VertexID).
				if (inInput->location == uint32_t(-1))
					continue;

				auto& outInput = _desc.inputs.emplace_back();

				outInput.semantic = inInput->semantic;
				outInput.location = inInput->location;
				outInput.format = SPV::API_GetFormat(inInput->format);
				outInput.size = SPV::API_GetSizeFromFormat(inInput->format);
			}
		}

		// Bindings
		{
			uint32_t count = 0u;
			spvReflectEnumerateDescriptorSets(&module, &count, nullptr);
			std::vector<SpvReflectDescriptorSet*> descSets(count);
			spvReflectEnumerateDescriptorSets(&module, &count, descSets.data());

			for (auto inDescSet : descSets)
			{
				auto& outDescSet = _desc.sets.emplace_back();

				for (size_t i = 0; i < inDescSet->binding_count; ++i)
				{
					auto& inDesc = *inDescSet->bindings[i];
					auto& outDesc = outDescSet.bindings.emplace_back();

					outDesc.name = inDesc.name;
					outDesc.binding = inDesc.binding;
					outDesc.num = inDesc.count;
					outDesc.type = SPV::sBindingTypeMap[(uint32_t)inDesc.descriptor_type];
				}
			}
		}


		spvReflectDestroyShaderModule(&module);

		return true;
	}

	ShaderCompileResult ShaderCompiler::CompileSPIRV(const ShaderCompileInfo& _info)
	{
		ShaderCompileResult result;

		SourceBuffer src;
		if (!ReadSourceShader(_info.path, src))
			return result;


		std::list<std::wstring> strBuff;
		std::vector<LPCWSTR> cArgs = ProcessParams(_info, strBuff);
		cArgs.push_back(L"-spirv"); // Add SPIRV compile option.
		cArgs.push_back(L"-fspv-reflect"); // Better SPIRV reflection.


		CComPtr<IDxcResult> compilResult = Compile_Internal(src.dx, cArgs, _info, result);

		if(!compilResult)
			return result;


		CComPtr<IDxcBlob> shader;
		SA_DXC_API(compilResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shader), nullptr));

		if(!ReflectSPIRV(shader, result.desc))
			return result;

		// Move to SPIRV-raw data type.
		result.rawSPIRV.data.resize(shader->GetBufferSize() / sizeof(decltype(result.rawSPIRV.data)::value_type));
		std::memmove(result.rawSPIRV.data.data(), shader->GetBufferPointer(), shader->GetBufferSize());

		result.bSuccess = true;
		SA_LOG((L"Shader {%1:%2} compilation success!", _info.path, _info.entrypoint), Normal, SA.Render.ShaderCompiler);

		return result;
	}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENGL_IMPL
}
