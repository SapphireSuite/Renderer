# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto)



# Executable

## Add executable target.
add_executable(SA_RenderProto "main.cpp")



# Dependencies

## Add library dependencies.
target_link_libraries(SA_RenderProto PRIVATE SA_Render glfw assimp SA_stb)


## Copy Resources command
### Render Global resources.
add_custom_command(TARGET SA_RenderProto POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Resources
	$<TARGET_FILE_DIR:SA_RenderProto>/Resources
)

### Tests resources.
add_custom_command(TARGET SA_RenderProto POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Tests/Resources
	$<TARGET_FILE_DIR:SA_RenderProto>/Resources
)



# Tests

add_test(NAME CSA_RenderProto COMMAND SA_RenderProto)
