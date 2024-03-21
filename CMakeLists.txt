# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

# Sapphire Suite's CMake tools.
add_subdirectory(ThirdParty/SA/CMake)



# Project

project(SA_Render)
SA_ConfigureProject(SA_Render)


# Main Library
add_library(SA_Render INTERFACE)
SA_ConfigureTarget(SA_Render LINK INTERFACE)



# Main LowLevel lib.
add_library(SA_Render_LowLevel INTERFACE)
SA_ConfigureTarget(SA_Render_LowLevel LINK INTERFACE)

### Link to main lib.
target_link_libraries(SA_Render INTERFACE SA_Render_LowLevel)



# LowLevel Common
add_library(SA_Render_LowLevel_Common STATIC)
SA_ConfigureTarget(SA_Render_LowLevel_Common)
SA_TargetSources(SA_Render_LowLevel_Common
	PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/Common"
	PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/Common"
)

### Link dependencies.
target_link_libraries(SA_Render_LowLevel_Common PUBLIC SA_Logger SA_Maths)

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



# Main RHI libs.
option(SA_RENDER_RHI_OPT "Should compile RHI" ON)

if(SA_RENDER_RHI_OPT)

	## Main RHI lib.
	add_library(SA_Render_RHI INTERFACE)
	SA_ConfigureTarget(SA_Render_RHI LINK INTERFACE)


	## RHI Common lib
	add_library(SA_Render_RHI_Common STATIC)
	SA_ConfigureTarget(SA_Render_RHI_Common)
	SA_TargetSources(SA_Render_RHI_Common
		PUBLIC_SRC_DIR "Include/SA/Render/RHI/Common"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/RHI/Common"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_RHI_Common
		PUBLIC SA_Render_LowLevel SA_Render_ShaderCompiler
	)

	### Link to main lib.
	target_link_libraries(SA_Render_RHI INTERFACE SA_Render_RHI_Common)

endif()



# Vulkan Wrapper
option(SA_RENDER_VULKAN_OPT "Should compile Vulkan wrapper" ON)

if(SA_RENDER_VULKAN_OPT)

	find_package(Vulkan REQUIRED)

	## LowLevel Vulkan
	add_library(SA_Render_LowLevel_Vulkan STATIC)
	SA_ConfigureTarget(SA_Render_LowLevel_Vulkan)
	SA_TargetSources(SA_Render_LowLevel_Vulkan
		PUBLIC_SRC_DIR "Include/SA/Render/LowLevel/Vulkan"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/LowLevel/Vulkan"
	)

	#### Link dependencies.
	target_link_libraries(SA_Render_LowLevel_Vulkan
		PUBLIC SA_Render_LowLevel_Common
		PUBLIC Vulkan::Vulkan # Set to public for easier wrapping.
	)

	#### Link to main lib.
	target_link_libraries(SA_Render_LowLevel INTERFACE SA_Render_LowLevel_Vulkan)


	## RHI Vulkan
	if(SA_RENDER_RHI_OPT)
		add_library(SA_Render_RHI_Vulkan STATIC)
		SA_ConfigureTarget(SA_Render_RHI_Vulkan)
		SA_TargetSources(SA_Render_RHI_Vulkan
			PUBLIC_SRC_DIR "Include/SA/Render/RHI/Vulkan"
			PUBLIC_INCL_DIR "OFF"
			PRIVATE_SRC_DIR "Source/SA/Render/RHI/Vulkan"
		)

		#### Link dependencies.
		target_link_libraries(SA_Render_RHI_Vulkan
			PUBLIC SA_Render_RHI_Common
			PUBLIC SA_Render_LowLevel_Vulkan # Set to public for easier wrapping.
		)

		#### Link to main lib.
		target_link_libraries(SA_Render_RHI INTERFACE SA_Render_RHI_Vulkan)
	endif()

endif()



# DX12 Wrapper
option(SA_RENDER_DX12_OPT "Should compile DirectX12 wrapper" OFF)

if(SA_RENDER_DX12_OPT AND WIN32)

	## LowLevel DX12
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


	## RHI DX12
	if(SA_RENDER_RHI_OPT)
		add_library(SA_Render_RHI_DX12 STATIC)
		SA_ConfigureTarget(SA_Render_RHI_DX12)
		SA_TargetSources(SA_Render_RHI_DX12
			PUBLIC_SRC_DIR "Include/SA/Render/RHI/DX12"
			PUBLIC_INCL_DIR "OFF"
			PRIVATE_SRC_DIR "Source/SA/Render/RHI/DX12"
		)

		#### Link dependencies.
		target_link_libraries(SA_Render_RHI_DX12
			PUBLIC SA_Render_RHI_Common
			PUBLIC SA_Render_LowLevel_DX12 # Set to public for easier wrapping.
		)

		#### Link to main lib.
		target_link_libraries(SA_Render_RHI INTERFACE SA_Render_RHI_DX12)
	endif()

endif()


## OpenGL
option(SA_RENDER_OPENGL_OPT "Should compile OpenGL wrapper" OFF)

if(SA_RENDER_OPENGL_OPT)

	find_package(OpenGL REQUIRED)

	## LowLevel OpenGL
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


	## RHI OpenGL
	if(SA_RENDER_RHI_OPT)
		add_library(SA_Render_RHI_OpenGL STATIC)
		SA_ConfigureTarget(SA_Render_RHI_OpenGL)
		SA_TargetSources(SA_Render_RHI_OpenGL
			PUBLIC_SRC_DIR "Include/SA/Render/RHI/OpenGL"
			PUBLIC_INCL_DIR "OFF"
			PRIVATE_SRC_DIR "Source/SA/Render/RHI/OpenGL"
		)

		#### Link dependencies.
		target_link_libraries(SA_Render_RHI_OpenGL
			PUBLIC SA_Render_RHI_Common
			PUBLIC SA_Render_LowLevel_OpenGL # Set to public for easier wrapping.
		)

		#### Link to main lib.
		target_link_libraries(SA_Render_RHI INTERFACE SA_Render_RHI_OpenGL)
	endif()

endif()


## Renderer
option(SA_RENDER_RENDERER_OPT "Should compile Renderer" ON)

if(SA_RENDER_RENDERER_OPT AND SA_RENDER_RHI_OPT)

	add_library(SA_Render_Renderer STATIC)
	SA_ConfigureTarget(SA_Render_Renderer)
	SA_TargetSources(SA_Render_Renderer
		PUBLIC_SRC_DIR "Include/SA/Render/Renderer"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/Renderer"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_Renderer
		PUBLIC SA_Render_RHI
	)

	### Link to main lib.
	target_link_libraries(SA_Render INTERFACE SA_Render_Renderer)

endif()


## ShaderCompiler
option(SA_RENDER_SHADER_COMPILER_OPT "Should compile shader compiler" ON)

if(SA_RENDER_SHADER_COMPILER_OPT)

	add_library(SA_Render_ShaderCompiler STATIC)
	SA_ConfigureTarget(SA_Render_ShaderCompiler)
	SA_TargetSources(SA_Render_ShaderCompiler
		PUBLIC_SRC_DIR "Include/SA/Render/ShaderCompiler"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/ShaderCompiler"
	)

	### Link dependencies.
	target_link_libraries(SA_Render_ShaderCompiler
		PUBLIC SA_Logger SA_DirectXShaderCompiler SA_Render_RHI
	)

	if(SA_RENDER_VULKAN_OPT OR SA_RENDER_OPENGL_OPT)
		target_link_libraries(SA_Render_ShaderCompiler PRIVATE spirv-reflect-static)
	endif()

	### Link to main lib.
	target_link_libraries(SA_Render INTERFACE SA_Render_ShaderCompiler)

	### Add source folder for shader include directory.
	target_compile_definitions(SA_Render_ShaderCompiler PRIVATE SA_CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

	if(WIN32)
		### Fix dxcompiler.dll mUtils->CreateReflection.
		add_custom_command(
			TARGET SA_Render_ShaderCompiler POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/ThirdParty/DirectXShaderCompiler/bin/windows/dxcompiler.dll
			$<TARGET_FILE_DIR:SA_Render_ShaderCompiler>/../
		)

		### Fix dxil.dll lookup.
		add_custom_command(
			TARGET SA_Render_ShaderCompiler POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/ThirdParty/DirectXShaderCompiler/bin/windows/dxil.dll
			$<TARGET_FILE_DIR:SA_Render_ShaderCompiler>/../
		)
	endif()

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
