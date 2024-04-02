// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX_COMPILER_API_GUARD
#define SAPPHIRE_RENDER_DX_COMPILER_API_GUARD

/**
*	\file DX12API.hpp
*
*	\brief \b dxcompiler support file.
*
*	\ingroup Render_DXC
*	\{
*/

#include <SA/Support/Compilers.hpp>
#include <SA/Support/API/Windows.hpp>

#if SA_UNIX && SA_CLANG
// Force UUID emulation on unix clang.
#define __EMULATE_UUID 1
#endif

#include <dxc/dxcapi.h>

// Must be include after __EMULATE_UUID and dxcapi.h.
#include "Exception_DXC.hpp"

#if SA_RENDER_API_TRACKING || defined(SA_DOXIGEN)

	/**
	 * \def SA_DXC_API(_dxcFunc, ...) 
	 * 
	 * \brief Sapphire DirectXCompiler-specific API call macro.
	 * Helper macro to track DX12 API calls and use
	 * Assertion macro with Exception_DX12/Exception_Default type and SA.Render.DX12.API channel.
	 * Input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _dxcFunc	DX12 function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_DXC_API(_dxcFunc, ...)\
	{\
		using RType = decltype(_dxcFunc);\
	\
		[&]<typename T>(T)\
		{\
			if constexpr (std::is_same_v<RType, HRESULT>)\
				SA_ASSERT((DXC, _dxcFunc), SA.Render.ShaderCompiler.DXC.API, ##__VA_ARGS__)\
			else if constexpr (std::is_same_v<RType, bool>)\
				SA_ASSERT((Default, _dxcFunc), SA.Render.ShaderCompiler.DXC.API, ##__VA_ARGS__)\
			else\
			{\
				_dxcFunc;\
				SA_LOG(#_dxcFunc, AssertSuccess, SA.Render.ShaderCompiler.DXC.API, ##__VA_ARGS__)\
			}\
		}(0);\
	}

	/**
	 * Use templated lambda to force if constexpr branch-instantiation.
	 * Source: https://stackoverflow.com/questions/50051473/if-constexpr-in-c17-does-not-work-in-a-non-templated-function
	*/

#else

	// Execute DXC function without logging or assertion check.
	#define SA_DXC_API(_dxcFunc, ...) { _dxcFunc; }

#endif

#if SA_WIN

#include <wrl.h> // ComPtr

template <typename T>
using CComPtr = Microsoft::WRL::ComPtr<T>;

#endif

/** \} */

#endif // SAPPHIRE_RENDER_DX_COMPILER_API_GUARD
