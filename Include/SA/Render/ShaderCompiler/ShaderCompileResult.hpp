// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD

#include <string>
#include <unordered_set>

#include <SA/Render/RHI/Shader/Descriptor/ShaderDescriptor.hpp>

namespace SA::RND
{
	struct ShaderCompileResult
	{
		bool bSuccess = false;

		std::unordered_set<std::wstring> includedFiles;

		RHI::ShaderDescriptor desc;

		inline operator bool() const noexcept { return bSuccess; }
	};
}

#endif // SAPPHIRE_RENDER_SHADER_COMPILE_RESULT_GUARD
