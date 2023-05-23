// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/D12WindowSurface.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::DX12
{
	void WindowSurface::Create(HWND&& _handle)
	{
		mHandle = std::move(_handle);

		SA_LOG(L"Window Surface created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle));
	}
	
	void WindowSurface::Destroy()
	{
		// Destroyed by Window Manager.

		SA_LOG(L"Window Surface destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle));

		mHandle = nullptr;
	}


	WindowSurface::operator HWND() const noexcept
	{
		return mHandle;
	}
}
