# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Entrypoints

## Sapphire Suite Third Party.
add_subdirectory(SA)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Disable assimp built as shared libraries")
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable assimp install")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable assimp build tests")
add_subdirectory(assimp)

add_subdirectory(stb)

if(SA_RENDER_SHADER_COMPILER_OPT)
	add_subdirectory(DirectXShaderCompiler)

	if(SA_RENDER_VULKAN_OPT OR SA_RENDER_OPENGL_OPT)
		set(SPIRV_REFLECT_EXECUTABLE OFF CACHE BOOL "Disable build spirv-reflect executable")
		set(SPIRV_REFLECT_EXAMPLES OFF CACHE BOOL "Disable build spirv-reflect examples")
		set(SPIRV_REFLECT_STATIC_LIB ON CACHE BOOL "Enable build SPIRV-Reflect static library")
		add_subdirectory(SPIRV-Reflect)
	endif()
endif()