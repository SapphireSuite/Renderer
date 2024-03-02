// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_TEXTURE_GUARD
#define SAPPHIRE_RENDER_D12_TEXTURE_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

namespace SA::RND::DX12
{
	class Device;
	class ResourceInitializer;

	class Texture
	{
		MComPtr<ID3D12Resource> mHandle;

	public:
		/// Create Texture from raw texture input.
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_D12_TEXTURE_GUARD
