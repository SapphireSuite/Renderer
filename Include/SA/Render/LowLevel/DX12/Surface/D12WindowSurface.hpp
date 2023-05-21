// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD

#include <Windows.h>

namespace SA
{
	class AWindow;

	namespace RND::DX12
	{
		class WindowSurface
		{
			HWND mHandle;
		
		public:
			void InitializeHandle(HWND&& _handle);

			void Create(const Factory& _factory, AWindow* _window);
			void Destroy(const Factory& _factory);

			operator HWND() const noexcept;
		};
	}
}

#endif // SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD
