// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPIRV_REFLECT_API_GUARD
#define SAPPHIRE_RENDER_SPIRV_REFLECT_API_GUARD

/**
*	\file SPIRV-Reflect.hpp
*
*	\brief \b SPIRV-Reflect support file.
*
*	\ingroup Render_DXC
*	\{
*/

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENLG_IMPL

#include <spirv_reflect.h>


#if SA_RENDER_API_TRACKING || defined(SA_DOXIGEN)

	/**
	 * \def SA_SPIRVR_API(_spvRFunc, ...) 
	 * 
	 * \brief Sapphire SPIRV-Reflect API call macro.
	 * Helper macro to track DX12 API calls and use
	 * Assertion macro with Exception_DX12/Exception_Default type and SA.Render.DX12.API channel.
	 * Input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _dxcFunc	DX12 function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_SPIRVR_API(_spvRFunc, ...)\
	{\
		using RType = decltype(_spvRFunc);\
	\
		[&]<typename T>(T)\
		{\
			if constexpr (std::is_same_v<RType, SpvReflectResult>)\
				SA_ASSERT((Equals, _spvRFunc, SPV_REFLECT_RESULT_SUCCESS), SA.Render.ShaderCompiler.SPIRVR.API, ##__VA_ARGS__)\
			else if constexpr (std::is_same_v<RType, bool>)\
				SA_ASSERT((Default, _spvRFunc), SA.Render.ShaderCompiler.SPIRVR.API, ##__VA_ARGS__)\
			else\
			{\
				_spvRFunc;\
				SA_LOG(#_spvRFunc, AssertSuccess, SA.Render.ShaderCompiler.SPIRVR.API, ##__VA_ARGS__)\
			}\
		}(0);\
	}

	/**
	 * Use templated lambda to force if constexpr branch-instantiation.
	 * Source: https://stackoverflow.com/questions/50051473/if-constexpr-in-c17-does-not-work-in-a-non-templated-function
	*/

#else

	// Execute DXC function without logging or assertion check.
	#define SA_SPIRVR_API(_spvRFunc, ...) { _spvRFunc; }

#endif

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL || SA_RENDER_LOWLEVEL_OPENLG_IMPL


/** \} */

#endif // SAPPHIRE_RENDER_SPIRV_REFLECT_API_GUARD
