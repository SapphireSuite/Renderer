# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto_DX12)



# Executable

## Add executable target.
add_executable(SA_RenderProto_DX12 "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_DX12 PRIVATE SA_Render glfw)

### Copy Resources command
add_custom_command(TARGET SA_RenderProto_DX12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Resources
	$<TARGET_FILE_DIR:SA_RenderProto_DX12>/Resources
)



# Tests

add_test(NAME CSA_RenderProto_DX12 COMMAND SA_RenderProto_DX12)
