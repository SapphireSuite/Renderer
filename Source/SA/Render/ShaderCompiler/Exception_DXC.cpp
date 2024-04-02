// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <DXCAPI.hpp>
//#include <Exception_DXC.hpp>

namespace SA::RND
{
	Exception_DXC::Exception_DXC(
		BaseInfo _info,
		HRESULT _hrRes,
		std::wstring _predStr
	) noexcept :
		Exception(std::move(_info),
			SUCCEEDED(_hrRes),
			std::move(_predStr) + L" == " + SA::ToWString(_hrRes))
	{
	}
}
