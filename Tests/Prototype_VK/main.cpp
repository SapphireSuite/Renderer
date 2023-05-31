// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>
using namespace SA::RND;

int main()
{
	SA::Debug::InitDefaultLogger();
	

	ShaderCompiler compiler;

	compiler.Create();	


	ShaderCompilInfo vsInfo
	{
		.path = L"Resources/Shaders/Forward/unlit.hlsl",
		.entrypoint = L"mainVS",
		.target = L"vs_6_5",
		.defines{L"SA_HAS_UV"}
	};

	compiler.CompileSPIRV(vsInfo);


	ShaderCompilInfo psInfo
	{
		.path = L"Resources/Shaders/Forward/unlit.hlsl",
		.entrypoint = L"mainPS",
		.target = L"ps_6_5",
		.defines{L"SA_HAS_UV"}
	};

	compiler.CompileSPIRV(psInfo);


	compiler.Destroy();	

	return 0;
}
