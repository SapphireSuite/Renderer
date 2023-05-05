# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

# Sapphire Suite's CMake tools.
add_subdirectory(CMake)



# Project

project(SA_Render)
SA_ConfigureProject(SA_Render)


# Main Library
add_library(SA_Render INTERFACE)
SA_ConfigureTarget(SA_Render LINK INTERFACE)



# Low-level wrapper Libraries


## Main LowLevel lib
add_library(SA_Render_LowLevel INTERFACE)
SA_ConfigureTarget(SA_Render_LowLevel LINK INTERFACE)

### Link to main lib.
target_link_libraries(SA_Render INTERFACE SA_Render_LowLevel)


## LowLevel Common
add_library(SA_Render_LowLevel_Common STATIC)
SA_ConfigureTarget(SA_Render_LowLevel_Common)
SA_TargetSources(SA_Render_LowLevel_Common
	PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/Common"
	PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/Common"
)

### Link dependencies.
target_link_libraries(SA_Render_LowLevel_Common PUBLIC SA_Logger)

### Link to main lib.
target_link_libraries(SA_Render_LowLevel INTERFACE SA_Render_LowLevel_Common)

### Validation layers
option(SA_RENDER_VALIDATION_LAYER_RELEASE_OPT "Enable render validation layers in release" OFF)

if(SA_RENDER_VALIDATION_LAYER_RELEASE_OPT)

	target_compile_definitions(SA_Render_LowLevel_Common PUBLIC SA_RENDER_VALIDATION_LAYER_RELEASE=1)

endif()

### API Tracking
option(SA_RENDER_API_TRACKING_OPT "Enable API call tracking" OFF)

if(SA_RENDER_API_TRACKING_OPT)

	target_compile_definitions(SA_Render_LowLevel_Common PUBLIC SA_RENDER_API_TRACKING=1)

endif()


## Vulkan Wrapper
option(SA_RENDER_VULKAN_OPT "Should compile Vulkan wrapper" ON)

if(SA_RENDER_VULKAN_OPT)

	find_package(Vulkan REQUIRED FATAL_ERROR)

	add_library(SA_Render_LowLevel_Vulkan STATIC)
	SA_ConfigureTarget(SA_Render_LowLevel_Vulkan)
	SA_TargetSources(SA_Render_LowLevel_Vulkan
		PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/Vulkan"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/Vulkan"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_LowLevel_Vulkan
		PUBLIC SA_Render_LowLevel_Common
		PUBLIC Vulkan::Vulkan # Set to public for easier wrapping.
		PRIVATE 
	)

	### Link to main lib.
	target_link_libraries(SA_Render_LowLevel INTERFACE SA_Render_LowLevel_Vulkan)

endif()


## DX12 Wrapper
option(SA_RENDER_DX12_OPT "Should compile DirectX12 wrapper" OFF)

if(SA_RENDER_DX12_OPT)

	add_library(SA_Render_LowLevel_DX12 STATIC)
	SA_ConfigureTarget(SA_Render_LowLevel_DX12)
	SA_TargetSources(SA_Render_LowLevel_DX12
		PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/DX12"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/DX12"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_LowLevel_DX12
		PUBLIC SA_Render_LowLevel_Common
		PUBLIC d3d12.lib dxgi.lib # Set to public for easier wrapping.
		PRIVATE dxguid.lib
	)

	### Link to main lib.
	target_link_libraries(SA_Render_LowLevel INTERFACE SA_Render_LowLevel_DX12)

endif()


## OpenGL
option(SA_RENDER_OPENGL_OPT "Should compile OpenGL wrapper" OFF)

if(SA_RENDER_OPENGL_OPT)

	find_package(OpenGL REQUIRED)

	add_library(SA_Render_LowLevel_OpenGL STATIC)
	SA_ConfigureTarget(SA_Render_LowLevel_OpenGL)
	SA_TargetSources(SA_Render_LowLevel_OpenGL
		PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/OpenGL"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/OpenGL"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_LowLevel_OpenGL
		PUBLIC SA_Render_LowLevel_Common
		PRIVATE OpenGL::GL
	)

	### Link to main lib.
	target_link_libraries(SA_Render_LowLevel INTERFACE SA_Render_LowLevel_OpenGL)

endif()



# Options

## Add SA_Render's tests to build tree.
option(SA_RENDER_BUILD_TESTS_OPT "Should build SA_Render tests" OFF)



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_RENDER_BUILD_TESTS_OPT)

	### Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)

endif()
