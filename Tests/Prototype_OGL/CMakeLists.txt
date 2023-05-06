# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto_OGL)



# Executable

## Add executable target.
add_executable(SA_RenderProto_OGL "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_OGL PRIVATE SA_Render)



# Tests

add_test(NAME CSA_RenderProto_OGL COMMAND SA_RenderProto_OGL)
