# Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

# Content
find_package(glfw CONFIG)

if(NOT TARGET glfw)

	message("Fetching GLFW...")

	FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw
		GIT_TAG        master
		SOURCE_DIR		${CMAKE_SOURCE_DIR}/ThirdParty/glfw
	)

	FetchContent_MakeAvailable(glfw)

endif()



# Entrypoints

add_subdirectory(Prototype)
add_subdirectory(Prototype_VK)
add_subdirectory(Prototype_DX12)
add_subdirectory(Prototype_OGL)
