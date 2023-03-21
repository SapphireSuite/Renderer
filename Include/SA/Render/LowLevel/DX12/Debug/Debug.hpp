// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEBUG_GUARD
#define SAPPHIRE_RENDER_DX12_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_DX12.hpp"
#include "SetDebugName.hpp"

#define SA_DX12_VALIDATION_LAYERS (SA_DEBUG || SA_RENDER_VALIDATION_LAYER_RELEASE)

#if SA_DEBUG || SA_LOG_RELEASE_OPT || defined(SA_DOXIGEN)

	/**
	 * \def SA_DX12_ASSERT(_dxFunc, ...) 
	 * 
	 * \brief Sapphire DX12-specific assertion macro.
	 * Helper macro to use Assertion macro with Exception_DX12 type and SA.Render.DX12 channel
	 * The input function will still be called even when logging and assertion are disabled.
	 * 
	 * \param[in] _dxFunc	DX12 function to call.
	 * \param[in] ...		Optional details
	 */
	#define SA_DX12_ASSERT(_dxFunc, ...) SA_ASSERT((DX12, _dxFunc), SA.Render.DX12, ##__VA_ARGS__)

#else

	// Execute Vk function without logging.
	#define SA_DX12_ASSERT(_dxFunc, ...) { _dxFunc; }

#endif

#endif // SAPPHIRE_RENDER_DX12_DEBUG_GUARD
