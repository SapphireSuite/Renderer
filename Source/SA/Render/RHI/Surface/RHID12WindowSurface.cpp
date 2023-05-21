// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHID12WindowSurface.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12WindowSurface::Create(const RenderInterface* _renderIntf, const WND::WHI::Window* _window)
	{
		mHandle.Create(*_renderIntf->API_DirectX12(), _window);
	}

	void D12WindowSurface::Destroy(const RenderInterface* _renderIntf)
	{
		mHandle.Destroy(*_renderIntf->API_DirectX12());
	}


	const D12::WindowSurface* D12WindowSurface::API_DirectX12() const
	{
		return &mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
