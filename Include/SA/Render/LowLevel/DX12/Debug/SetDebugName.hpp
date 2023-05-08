// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDE_DX12_SET_DEBUG_NAME_GUARD
#define SAPPHIRE_RENDE_DX12_SET_DEBUG_NAME_GUARD

#include <d3d12.h>
#include <string_view>

namespace SA::RND
{
	namespace DX12
	{
		void SetDebugName(ID3D12Object* _obj, std::string_view _name);
		void SetDebugName(ID3D12Object* _obj, std::wstring_view _name);
	}
}

#endif // SAPPHIRE_RENDE_DX12_SET_DEBUG_NAME_GUARD
