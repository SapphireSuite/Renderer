// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_D12_CUBEMAP_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawCubemap.hpp>

namespace SA::RND::DX12
{
	class Device;
	class ResourceInitializer;

	class Cubemap
	{
		MComPtr<ID3D12Resource> mTexture;
		MComPtr<ID3D12Resource> mIrradiance;

	public:
		/// Create Cubemap from raw cubemap input.
		void Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_D12_CUBEMAP_GUARD
