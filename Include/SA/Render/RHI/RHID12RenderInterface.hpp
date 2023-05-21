// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_RENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_RHI_D12_RENDER_INTERFACE_GUARD

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include "RHIRenderInterface.hpp"

#include <SA/Render/LowLevel/DX12/D12Factory.hpp>

namespace SA::RND::RHI
{
	class D12RenderInterface : public RenderInterface
	{
		DX12::Factory mFactory;

	public:
		void Create() override final;
		void Destroy() override final;

//{ WindowSurface

	protected:
		WindowSurface* InstantiateWindowSurfaceClass() const override final;

//}


//{ Device

	protected:
		Device* InstantiateDeviceClass() const override final;

	public:
		std::vector<std::shared_ptr<DeviceInfo>> QueryDeviceInfos() const override final;

//}

	public:
		const DX12::Factory* API_DirectX12() const override final;
	};
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

#endif // SAPPHIRE_RENDER_RHI_D12_RENDER_INTERFACE_GUARD
