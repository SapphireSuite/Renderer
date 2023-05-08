// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Debug/SetDebugName.hpp>

#include <Debug/Debug.hpp>

namespace SA::RND::DX12
{
	void SetDebugName(ID3D12Object* _obj, std::string_view _name)
	{
#if SA_DX12_VALIDATION_LAYERS

		_obj->SetName(SA::ToWString(_name.data()).c_str());

#endif // SA_DX12_VALIDATION_LAYERS
	}

	void SetDebugName(ID3D12Object* _obj, std::wstring_view _name)
	{
#if SA_DX12_VALIDATION_LAYERS

		_obj->SetName(_name.data());

#endif // SA_DX12_VALIDATION_LAYERS
	}
}
