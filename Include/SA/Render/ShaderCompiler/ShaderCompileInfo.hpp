// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_COMPILE_INFO_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPILE_INFO_GUARD

#include <string>
#include <vector>

namespace SA::RND
{
	class ShaderCompileInfo
	{
	public:
		std::wstring path;

		std::wstring entrypoint = L"main";

		std::wstring target;

		std::wstring standard = L"2021";

		std::vector<std::wstring> defines;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILE_INFO_GUARD
