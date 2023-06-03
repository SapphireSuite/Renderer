// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>
using namespace SA::RND;

int main()
{
	SA::Debug::InitDefaultLogger();
	

	ShaderCompiler compiler;

	compiler.Create();	


	ShaderCompileInfo vsInfo
	{
		.path = L"Resources/Shaders/Forward/Unlit.hlsl",
		.entrypoint = L"mainVS",
		.target = L"vs_6_5",
		.defines{L"SA_HAS_UV", L"SA_ALBEDO_ID=0"}
	};

	ShaderCompileResult vsShaderRes = compiler.CompileSPIRV(vsInfo);


	ShaderCompileInfo psInfo
	{
		.path = L"Resources/Shaders/Forward/Unlit.hlsl",
		.entrypoint = L"mainPS",
		.target = L"ps_6_5",
		.defines{L"SA_HAS_UV", L"SA_ALBEDO_ID=0"}
	};

	ShaderCompileResult psShaderRes = compiler.CompileSPIRV(psInfo);


	compiler.Destroy();	

	return 0;
}
