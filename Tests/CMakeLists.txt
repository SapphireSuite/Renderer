# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

# Content
find_package(glfw CONFIG)

# Fetch if not found
SA_FetchOrInclude(
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG        master
)



# Entrypoints

add_subdirectory(Prototype)

if(SA_RENDER_VULKAN_OPT)
	add_subdirectory(Prototype_VK)
endif()

if(SA_RENDER_DX12_OPT)
	add_subdirectory(Prototype_DX12)
endif()

if(SA_RENDER_OPENGL_OPT)
	add_subdirectory(Prototype_OGL)
endif()
