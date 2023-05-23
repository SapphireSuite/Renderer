// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHID12WindowSurface.hpp>

#include <RHIRenderInterface.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12WindowSurface::Create(const RenderInterface* _renderIntf, const IRenderWindow* _window)
	{
		(void)_renderIntf;

		mHandle.Create(_window->GetHWNDHandle());
	}

	void D12WindowSurface::Destroy(const RenderInterface* _renderIntf)
	{
		(void)_renderIntf;

		mHandle.Destroy();
	}


	const DX12::WindowSurface& D12WindowSurface::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
