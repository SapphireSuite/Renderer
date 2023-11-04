// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_RHI_D12_RESOURCE_INITIALIZER_GUARD

#include "RHIResourceInitializer.hpp"

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/D12ResourceInitializer.hpp>

namespace SA::RND::RHI
{
	class D12ResourceInitializer : public ResourceInitializer
	{
		DX12::ResourceInitializer mHandle;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

		DX12::ResourceInitializer& API_DirectX12() override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_D12_RESOURCE_INITIALIZER_GUARD
