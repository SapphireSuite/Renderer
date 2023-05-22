# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto)



# Executable

## Add executable target.
add_executable(SA_RenderProto "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto PRIVATE SA_Render glfw)



# Tests

add_test(NAME CSA_RenderProto COMMAND SA_RenderProto)
