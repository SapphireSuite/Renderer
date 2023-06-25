# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto_VK)



# Executable

## Add executable target.
add_executable(SA_RenderProto_VK "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_VK PRIVATE SA_Render glfw)

### Copy Resources command
add_custom_command(TARGET SA_RenderProto_VK POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Resources
	$<TARGET_FILE_DIR:SA_RenderProto_VK>/Resources
)



# Tests

add_test(NAME CSA_RenderProto_VK COMMAND SA_RenderProto_VK)
