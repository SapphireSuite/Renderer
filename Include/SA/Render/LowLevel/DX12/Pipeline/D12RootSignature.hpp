// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_ROOT_SIGNATURE_GUARD
#define SAPPHIRE_RENDER_DX12_ROOT_SIGNATURE_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class Device;

	using DXRootSignatureT = MComPtr<ID3D12RootSignature>;

	class RootSignature
	{
		DXRootSignatureT mHandle = nullptr;

	public:
		void Create(const Device& _device, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& _desc);
		void Destroy();

		DXRootSignatureT operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_ROOT_SIGNATURE_GUARD
