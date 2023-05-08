// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
#define SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD

#include <d3d12.h>

namespace SA::RND::DX12
{
	class ValidationLayers
	{
	public:
		static void Initialize();
		static void Uninitialize();

		static void DebugCallback(D3D12_MESSAGE_CATEGORY _category,
			D3D12_MESSAGE_SEVERITY _severity,
			D3D12_MESSAGE_ID _ID,
			LPCSTR _description,
			void* _context);
	};
}

#endif // SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
