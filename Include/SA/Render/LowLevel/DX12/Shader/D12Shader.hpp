// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_SHADER_GUARD
#define SAPPHIRE_RENDER_D12_SHADER_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class Shader
	{
		MComPtr<ID3DBlob> mHandle;

	public:
		void Create(MComPtr<ID3DBlob> _handle);
		void Destroy();

		ID3DBlob* operator->() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_D12_SHADER_GUARD
