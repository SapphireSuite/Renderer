// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_RHI_D12_CUBEMAP_GUARD

#include <SA/Render/RHI/Common/Texture/RHICubemap.hpp>

#include <SA/Render/LowLevel/DX12/Texture/D12Cubemap.hpp>

namespace SA::RND::RHI
{
	class D12Cubemap : public Cubemap
	{
		DX12::Cubemap mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawCubemap& _raw) override final;
		void Destroy(const Device* _device) override final;

		const DX12::Cubemap& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_CUBEMAP_GUARD
