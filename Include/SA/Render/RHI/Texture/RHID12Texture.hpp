// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_TEXTURE_GUARD

#include <SA/Render/RHI/Texture/RHITexture.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Texture/D12Texture.hpp>

namespace SA::RND::RHI
{
	class D12Texture : public Texture
	{
		DX12::Texture mHandle;

	public:
		void Create(const Device* _device, const SA::RND::TextureDescriptor& _desc) override final;
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) override final;
		void Destroy(const Device* _device) override final;

		const DX12::Texture& API_DirectX12() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_DX12_TEXTURE_GUARD
