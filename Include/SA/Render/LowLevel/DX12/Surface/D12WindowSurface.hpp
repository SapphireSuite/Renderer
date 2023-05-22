// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD

#include <Windows.h>

namespace SA
{
	namespace WND::WHI
	{
		class Window;
	}

	namespace RND::DX12
	{
		class Factory;

		class WindowSurface
		{
			HWND mHandle;
		
		public:
			void InitializeHandle(HWND&& _handle);

			void Create(const Factory& _factory, const WND::WHI::Window* _window);
			void Destroy(const Factory& _factory);

			operator HWND() const noexcept;
		};
	}
}

#endif // SAPPHIRE_RENDER_DX12_WINDOW_SURFACE_GUARD
