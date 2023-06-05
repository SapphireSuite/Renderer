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

		std::string entrypoint = "main";

		std::string target;

		std::string standard = "2021";

		std::vector<std::string> defines;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILE_INFO_GUARD
