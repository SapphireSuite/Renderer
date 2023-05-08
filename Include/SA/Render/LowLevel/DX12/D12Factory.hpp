// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_FACTORY_GUARD
#define SAPPHIRE_RENDER_DX12_FACTORY_GUARD

#include "DX12API.hpp"

namespace SA::RND::DX12
{
	using DXFactoryT = IDXGIFactory6*;

	class Factory
	{
		DXFactoryT mHandle = nullptr;

	public:
		void Create();
		void Destroy();

		DXFactoryT operator->() const;
	};
}

#endif	// SAPPHIRE_RENDER_DX12_FACTORY_GUARD
