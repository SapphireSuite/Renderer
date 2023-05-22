// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/D12WindowSurface.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::DX12
{
	void WindowSurface::InitializeHandle(HWND&& _handle)
	{
		mHandle = std::move(_handle);

		SA_LOG(L"Window Surface handle initialized.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle));
	}

	
	void WindowSurface::Create(const Factory& _factory, const WND::WHI::Window* _window)
	{
		// TODO: Implement with Sapphire Windowing lib.
		(void)_factory;
		(void)_window;
	}
	
	void WindowSurface::Destroy(const Factory& _factory)
	{
		(void)_factory;

		// Destroyed by Window Manager.
		mHandle = nullptr;
	}


	WindowSurface::operator HWND() const noexcept
	{
		return mHandle;
	}
}
