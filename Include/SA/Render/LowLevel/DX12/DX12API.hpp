// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX_12_API_GUARD
#define SAPPHIRE_RENDER_DX_12_API_GUARD

/**
*	\file DX12API.hpp
*
*	\brief \b d3d12.h support file.
*
*	\ingroup Render_DX12
*	\{
*/

#include <d3d12.h>
#include <dxgi1_6.h>

#include "Debug/Debug.hpp"

#if SA_RENDER_API_TRACKING || defined(SA_DOXIGEN)

	/**
	 * \def SA_DX12_API(_dxFunc, ...) 
	 * 
	 * \brief Sapphire DirectX12-specific API call macro.
	 * Helper macro to track DX12 API calls and use
	 * Assertion macro with Exception_DX12/Exception_Default type and SA.Render.DX12.API channel.
	 * Input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _dxFunc	DX12 function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_DX12_API(_dxFunc, ...)\
	{\
		using RType = decltype(_dxFunc);\
	\
		[&]<typename T>(T)\
		{\
			if constexpr (std::is_same_v<RType, HRESULT>)\
				SA_ASSERT((DX12, _dxFunc), SA.Render.DX12.API, ##__VA_ARGS__)\
			else if constexpr (std::is_same_v<RType, bool>)\
				SA_ASSERT((Default, _dxFunc), SA.Render.DX12.API, ##__VA_ARGS__)\
			else\
			{\
				_dxFunc;\
				SA_LOG(#_dxFunc, AssertSuccess, SA.Render.DX12.API, ##__VA_ARGS__)\
			}\
		}(0);\
	}

	/**
	 * Use templated lambda to force if constexpr branch-instantiation.
	 * Source: https://stackoverflow.com/questions/50051473/if-constexpr-in-c17-does-not-work-in-a-non-templated-function
	*/

#else

	// Execute DX12 function without logging or assertion check.
	#define SA_DX12_API(_dxFunc, ...) { _dxFunc; }

#endif

/** \} */

#endif // SAPPHIRE_RENDER_DIRECTX_12_API_GUARD
