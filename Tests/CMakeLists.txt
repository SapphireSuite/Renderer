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
add_subdirectory(Prototype_VK)
add_subdirectory(Prototype_DX12)
add_subdirectory(Prototype_OGL)
