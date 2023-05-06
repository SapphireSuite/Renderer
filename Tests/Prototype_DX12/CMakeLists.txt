# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderProto_DX12)



# Executable

## Add executable target.
add_executable(SA_RenderProto_DX12 "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_DX12 PRIVATE SA_Render)



# Tests

add_test(NAME CSA_RenderProto_DX12 COMMAND SA_RenderProto_DX12)
