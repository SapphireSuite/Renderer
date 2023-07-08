# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

add_library(SA_DirectXShaderCompiler INTERFACE)

target_include_directories(SA_DirectXShaderCompiler INTERFACE include)

if(UNIX)
	target_link_directories(SA_DirectXShaderCompiler INTERFACE bin/unix)
	target_link_libraries(SA_DirectXShaderCompiler INTERFACE libdxcompiler.so libdxil.so)
elseif(WIN32)
	target_link_directories(SA_DirectXShaderCompiler INTERFACE bin/windows)
	target_link_libraries(SA_DirectXShaderCompiler INTERFACE dxcompiler.dll)

	# Do not directly link with dxil.dll (`dxil.lib missing` error).
	# Calling dxcompiler.dll will lookup for dxil.dll: copy file next to .exe
	#target_link_libraries(SA_DirectXShaderCompiler INTERFACE dxil.dll)

	# Can't copy using file because of $<CONFIG>
	# Add custom command in SA_Render_ShaderCompiler target.
	#file(COPY bin/windows/dxil.dll DESTINATION ${SA_BIN_OUTPUT_DIR})
endif()
