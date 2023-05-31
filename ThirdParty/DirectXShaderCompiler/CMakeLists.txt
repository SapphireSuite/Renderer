# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

add_library(SA_DirectXShaderCompiler INTERFACE)

target_include_directories(SA_DirectXShaderCompiler INTERFACE include)

if(UNIX)
	target_link_directories(SA_DirectXShaderCompiler INTERFACE bin/unix)
	target_link_libraries(SA_DirectXShaderCompiler INTERFACE libdxcompiler.so libdxil.so)
endif()