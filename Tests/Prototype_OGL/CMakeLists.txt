# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto_OGL)



# Executable

## Add executable target.
add_executable(SA_RenderProto_OGL "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_OGL PRIVATE SA_Render)

### Copy Resources command
add_custom_command(TARGET SA_RenderProto_OGL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Resources
	$<TARGET_FILE_DIR:SA_RenderProto_OGL>/Resources
)



# Tests

add_test(NAME CSA_RenderProto_OGL COMMAND SA_RenderProto_OGL)
